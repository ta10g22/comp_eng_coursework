#ifndef CONTROLUNIT_H
#define CONTROLUNIT_H

#include "instructionmemory.h"
#include "registerfile.h"
#include "datamemory.h"
#include "pipelineregs.h"
#include "alu.h"
#include "programcounter.h"
#include "hazardunit.h"
#include <iostream>
#include <string>

// ControlUnit with Hazard detection, forwarding, and pipeline observability
class ControlUnit {
public:
    ControlUnit(InstructionMemory& imem,
                RegisterFile&      regs,
                DataMemory&        dmem,
                ProgramCounter&    pc);

    // Pipeline stage methods
    int UpdateInstructionFetch();
    int UpdateInstructionDecode();
    int UpdateInstructionExecute();
    int UpdateMemoryAccess();
    int UpdateWriteBack();

    // Advance pipeline registers each cycle and then display state
    void updatePipelineRegisters();

private:
    InstructionMemory& m_imem;
    RegisterFile&      m_regs;
    DataMemory&        m_dmem;
    ProgramCounter&    m_pc;
    ALU                m_alu;
    HazardUnit         m_hazard;

    // pipeline registers: current and next
    IFID  if_id,    if_id_next;
    IDEX  id_ex,    id_ex_next;
    EXMEM ex_mem,   ex_mem_next;
    MEMWB mem_wb,   mem_wb_next;

    // forward select lines
    int fwdA, fwdB;

    // Utility: print current pipeline state
    void printPipelineState() const;

    // Utility: format an instruction for display
    std::string formatInstr(const Instruction& instr) const;
};

#endif // CONTROLUNIT_H
