#include "controlunit.h"
#include <iostream>

ControlUnit::ControlUnit(InstructionMemory& imem,
                         RegisterFile&      regs,
                         DataMemory&        dmem,
                         ProgramCounter&    pc)
  : m_imem(imem)
  , m_regs(regs)
  , m_dmem(dmem)
  , m_pc(pc)
  , m_alu()
  , m_hazard()
  ,fwdA(0), fwdB(0)
{
    // clear valid flags
    if_id.valid = id_ex.valid = ex_mem.valid = mem_wb.valid = false;
    if_id_next.valid = id_ex_next.valid = ex_mem_next.valid = mem_wb_next.valid = false;
}

// ---------------- IF ----------------
int ControlUnit::UpdateInstructionFetch() {
    // stall if load‑use hazard detected
    bool stall = m_hazard.detectLoadUse(if_id, id_ex);
    if (stall) {
        // hold IF/ID as invalid and do not advance PC
        if_id_next.valid = false;
        return 0;
    }
    // fetch
    if_id_next.instr   = m_imem.fetch(m_pc.value());
    if_id_next.pcPlus1 = m_pc.value() + 1;
    if_id_next.valid   = true;
    m_pc.step();
    return 0;
}

// ---------------- ID ----------------
int ControlUnit::UpdateInstructionDecode() {
    if (!if_id.valid) { id_ex_next.valid = false; return 0; }

    const Instruction &ins = if_id.instr;
    id_ex_next.opcode    = ins.opcode;
    id_ex_next.rs        = ins.rs;
    id_ex_next.rt        = ins.rt;
    id_ex_next.rd        = ins.rd;
    id_ex_next.immediate = ins.immediate;
    id_ex_next.pcPlus1   = if_id.pcPlus1;

    id_ex_next.rsVal = m_regs.read(ins.rs);
    id_ex_next.rtVal = m_regs.read(ins.rt);
    id_ex_next.valid = true;
    return 0;
}

// ---------------- EX ----------------
int ControlUnit::UpdateInstructionExecute() {
    if (!id_ex.valid) { ex_mem_next.valid = false; return 0; }

    // compute forwarding signals
    m_hazard.computeForwarding(id_ex, ex_mem, mem_wb, fwdA, fwdB);

    int operandA = (fwdA == 1) ? ex_mem.aluResult : (fwdA == 2) ? ((mem_wb.opcode == "lw") ? mem_wb.memData : mem_wb.aluResult) : id_ex.rsVal;
    int operandBorig = id_ex.rtVal;
    int operandB = (fwdB == 1) ? ex_mem.aluResult : (fwdB == 2) ? ((mem_wb.opcode == "lw") ? mem_wb.memData : mem_wb.aluResult) : operandBorig;

    const std::string &op = id_ex.opcode;
    int aluOut = 0;
    bool takeBranch=false; int branchTarget=0; int writeReg=0;

    if (op == "add") { aluOut = m_alu.add(operandA, operandB); writeReg=id_ex.rd; }
    else if (op == "sub") { aluOut = m_alu.subtract(operandA, operandB); writeReg=id_ex.rd; }
    else if (op == "addi") { aluOut = m_alu.add(operandA, id_ex.immediate); writeReg=id_ex.rt; }
    else if (op=="lw"||op=="sw") { aluOut = m_alu.add(operandA, id_ex.immediate); writeReg = id_ex.rt; }
    else if (op=="beq") { takeBranch  = m_alu.branchifequal(operandA, operandB); branchTarget=id_ex.immediate; }
    else if (op=="j") { takeBranch=true; branchTarget=id_ex.immediate; }

    ex_mem_next.opcode = op;
    ex_mem_next.aluResult = aluOut;
    ex_mem_next.rtVal = operandBorig; // original RT for store
    ex_mem_next.writeReg = writeReg;
    ex_mem_next.branchTaken = takeBranch;
    ex_mem_next.branchTarget = branchTarget;
    ex_mem_next.valid = true;
    return 0;
}

// ---------------- MEM ----------------
int ControlUnit::UpdateMemoryAccess() {
    if (!ex_mem.valid) { mem_wb_next.valid = false; return 0; }
    const std::string &op = ex_mem.opcode;
    int memVal = 0;
    if (op=="lw") {
        memVal = m_dmem.loadWord(ex_mem.aluResult);
    } else if (op=="sw") {
        m_dmem.storeWord(ex_mem.aluResult, ex_mem.rtVal);
    }
    if (ex_mem.branchTaken) m_pc.set(ex_mem.branchTarget);

    mem_wb_next.opcode=op;
    mem_wb_next.memData=memVal;
    mem_wb_next.aluResult=ex_mem.aluResult;
    mem_wb_next.writeReg=ex_mem.writeReg;
    mem_wb_next.valid=true;
    return 0;
}

// ---------------- WB ----------------
int ControlUnit::UpdateWriteBack() {
    if (!mem_wb.valid) return 0;
    const std::string &op = mem_wb.opcode;
    if (op=="add"||op=="sub"||op=="addi") {
        m_regs.write(mem_wb.writeReg, mem_wb.aluResult);
    } else if (op=="lw") {
        m_regs.write(mem_wb.writeReg, mem_wb.memData);
    }
    return 0;
}

// ----------- Latch next → current ---------
void ControlUnit::updatePipelineRegisters() {
    if_id=if_id_next; id_ex=id_ex_next; ex_mem=ex_mem_next; mem_wb=mem_wb_next;
    if_id_next.valid=id_ex_next.valid=ex_mem_next.valid=mem_wb_next.valid=false;
}
