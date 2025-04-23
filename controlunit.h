#ifndef CONTROLUNIT_H
#define CONTROLUNIT_H

#include "instructionmemory.h"
#include "registerfile.h"
#include "datamemory.h"
#include "pipelineregs.h"
#include "alu.h"
#include "programcounter.h"
#include "hazardunit.h"


// ControlUnit with Hazard detection + Forwarding
class ControlUnit {
    public:
        ControlUnit(InstructionMemory& imem,
                    RegisterFile&      regs,
                    DataMemory&        dmem,
                    ProgramCounter&    pc);
    
        int UpdateInstructionFetch();   // IF stage
        int UpdateInstructionDecode();  // ID stage
        int UpdateInstructionExecute(); // EX stage
        int UpdateMemoryAccess();       // MEM stage
        int UpdateWriteBack();          // WB stage
    
        void updatePipelineRegisters(); // move "next" → "current"
    
    private:
        InstructionMemory& m_imem;
        RegisterFile&      m_regs;
        DataMemory&        m_dmem;
        ProgramCounter&    m_pc;
        ALU                m_alu;
        HazardUnit         m_hazard;
    
        // pipeline registers
        IFID  if_id,  if_id_next;
        IDEX  id_ex,  id_ex_next;
        EXMEM ex_mem, ex_mem_next;
        MEMWB mem_wb, mem_wb_next;
    
        // forward select lines (0=none,1=EX/MEM,2=MEM/WB)
        int fwdA, fwdB;
    };
    
    #endif 
    
