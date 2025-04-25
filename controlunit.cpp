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
  , fwdA(0)
  , fwdB(0)
{
    // pipeline starts empty
    if_id.valid = id_ex.valid = ex_mem.valid = mem_wb.valid = false;
    if_id_next.valid = id_ex_next.valid = ex_mem_next.valid = mem_wb_next.valid = false;
}

int ControlUnit::UpdateInstructionFetch() {
    // Stall on load-use hazard
    if (m_hazard.detectLoadUse(if_id, id_ex)) {
        if_id_next.valid = false;
        return 0;
    }

    // If PC still within instruction memory, fetch instruction
    if (m_pc.value() < static_cast<int>(m_imem.size())) {
        if_id_next.instr   = m_imem.fetch(m_pc.value());
        if_id_next.pcPlus1 = m_pc.value() + 1;
        if_id_next.valid   = true;
        m_pc.step();
    } else {
        // Past end of memory: inject NOP (bubble)
        if_id_next.valid = false;
        // Do NOT advance PC further
    }

    return 0;
}

int ControlUnit::UpdateInstructionDecode() {
    if (!if_id.valid) { id_ex_next.valid = false; return 0; }
    // DECODE stage
    id_ex_next.instr      = if_id.instr;
    id_ex_next.opcode     = if_id.instr.opcode;
    id_ex_next.rs         = if_id.instr.rs;
    id_ex_next.rt         = if_id.instr.rt;
    id_ex_next.rd         = if_id.instr.rd;
    id_ex_next.immediate  = if_id.instr.immediate;
    id_ex_next.pcPlus1    = if_id.pcPlus1;
    id_ex_next.rsVal      = m_regs.read(if_id.instr.rs);
    id_ex_next.rtVal      = m_regs.read(if_id.instr.rt);
    id_ex_next.valid      = true;
    return 0;
}

int ControlUnit::UpdateInstructionExecute() {
    if (!id_ex.valid) { ex_mem_next.valid = false; return 0; }
    // EXECUTE stage
    m_hazard.computeForwarding(id_ex, ex_mem, mem_wb, fwdA, fwdB);
    int opA = (fwdA == 1) ? ex_mem.aluResult
             : (fwdA == 2) ? ((mem_wb.opcode == "lw") ? mem_wb.memData : mem_wb.aluResult)
             : id_ex.rsVal;
    int origB = id_ex.rtVal;
    int opB = (fwdB == 1) ? ex_mem.aluResult
             : (fwdB == 2) ? ((mem_wb.opcode == "lw") ? mem_wb.memData : mem_wb.aluResult)
             : origB;

    ex_mem_next.instr       = id_ex.instr;
    ex_mem_next.opcode      = id_ex.opcode;
    ex_mem_next.aluResult   = 0;
    ex_mem_next.rtVal       = origB;
    ex_mem_next.writeReg    = 0;
    ex_mem_next.branchTaken = false;
    ex_mem_next.branchTarget= 0;

    const auto &op = id_ex.opcode;
    if (op == "add") {
        ex_mem_next.aluResult = m_alu.add(opA, opB);
        ex_mem_next.writeReg  = id_ex.rd;
    } else if (op == "sub") {
        ex_mem_next.aluResult = m_alu.subtract(opA, opB);
        ex_mem_next.writeReg  = id_ex.rd;
    } else if (op == "addi") {
        ex_mem_next.aluResult = m_alu.add(opA, id_ex.immediate);
        ex_mem_next.writeReg  = id_ex.rt;
    } else if (op == "lw" || op == "sw") {
        ex_mem_next.aluResult = m_alu.add(opA, id_ex.immediate);
        ex_mem_next.writeReg  = id_ex.rt;
    } else if (op == "beq") {
        ex_mem_next.branchTaken  = m_alu.branchifequal(opA, opB);
        ex_mem_next.branchTarget = id_ex.immediate;
    } else if (op == "j") {
        ex_mem_next.branchTaken  = true;
        ex_mem_next.branchTarget = id_ex.immediate;
    }
    ex_mem_next.valid = true;
    return 0;
}

int ControlUnit::UpdateMemoryAccess() {
    if (!ex_mem.valid) { mem_wb_next.valid = false; return 0; }
    // MEMORY stage
    mem_wb_next.instr     = ex_mem.instr;
    mem_wb_next.opcode    = ex_mem.opcode;
    mem_wb_next.aluResult = ex_mem.aluResult;
    mem_wb_next.writeReg  = ex_mem.writeReg;
    mem_wb_next.memData   = 0;

    if (ex_mem.opcode == "lw") {
        mem_wb_next.memData = m_dmem.loadWord(ex_mem.aluResult);
    } else if (ex_mem.opcode == "sw") {
        m_dmem.storeWord(ex_mem.aluResult, ex_mem.rtVal);
    }
    if (ex_mem.branchTaken) {
        m_pc.set(ex_mem.branchTarget);
    }
    mem_wb_next.valid = true;
    return 0;
}

int ControlUnit::UpdateWriteBack() {
    if (!mem_wb.valid) return 0;
    // WRITE-BACK stage
    if (mem_wb.opcode == "add" || mem_wb.opcode == "sub" || mem_wb.opcode == "addi") {
        m_regs.write(mem_wb.writeReg, mem_wb.aluResult);
    } else if (mem_wb.opcode == "lw") {
        m_regs.write(mem_wb.writeReg, mem_wb.memData);
    }
    return 0;
}

void ControlUnit::updatePipelineRegisters() {
    // next -> current
    if_id    = if_id_next;
    id_ex    = id_ex_next;
    ex_mem   = ex_mem_next;
    mem_wb   = mem_wb_next;

    // clear next pipeline registers
    if_id_next.valid = id_ex_next.valid = ex_mem_next.valid = mem_wb_next.valid = false;
    
    printPipelineState();
}

std::string ControlUnit::formatInstr(const Instruction &instr) const {
    if (instr.opcode.empty()) return "NOP";
    std::string s = instr.opcode;
    if (s == "add" || s == "sub") {
        s += " $" + std::to_string(instr.rd)
          + ", $" + std::to_string(instr.rs)
          + ", $" + std::to_string(instr.rt);
    } else if (s == "addi") {
        s += " $" + std::to_string(instr.rt)
          + ", $" + std::to_string(instr.rs)
          + ", "  + std::to_string(instr.immediate);
    } else if (s == "lw" || s == "sw") {
        s += " $" + std::to_string(instr.rt)
          + ", "  + std::to_string(instr.immediate)
          + "($" + std::to_string(instr.rs) + ")";
    } else if (s == "beq") {
        s += " $" + std::to_string(instr.rs)
          + ", $" + std::to_string(instr.rt)
          + ", "  + instr.label;
    } else if (s == "j") {
        s += " " + instr.label;
    }
    return s;
}

void ControlUnit::printPipelineState() const {
    std::cout << "[PIPELINE] IF/ID:   "
              << (if_id.valid   ? formatInstr(if_id.instr)   : "NOP") << "   |   "
              << "ID/EX:   "   << (id_ex.valid   ? formatInstr(id_ex.instr)   : "NOP") << "   |   "
              << "EX/MEM:  " << (ex_mem.valid  ? formatInstr(ex_mem.instr)  : "NOP") << "   |   "
              << "MEM/WB:  " << (mem_wb.valid  ? formatInstr(mem_wb.instr)  : "NOP")
              << std::endl;
}

bool ControlUnit::pipelineNotEmpty() const {
    return if_id.valid
        || id_ex.valid
        || ex_mem.valid
        || mem_wb.valid;
}
