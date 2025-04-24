// PipelineRegs.h
#ifndef PIPELINEREGS_H
#define PIPELINEREGS_H

#include "instruction.h"
#include <string>

// IF/ID pipeline register:
struct IFID {
    Instruction instr;  // fetched instruction
    int         pcPlus1;// next-instruction index
    bool        valid;  // is this slot holding real work?
};

// ID/EX pipeline register:
struct IDEX {
    Instruction instr;   // the instruction being decoded
    std::string opcode;  // duplicate of instr.opcode (for convenience)
    int         rs, rt, rd;
    int         rsVal, rtVal;
    int         immediate;
    int         pcPlus1;
    bool        valid;
};

// EX/MEM pipeline register:
struct EXMEM {
    Instruction instr;   // the instruction being executed
    std::string opcode;
    int         aluResult;
    int         rtVal;
    int         writeReg;
    bool        branchTaken;
    int         branchTarget;
    bool        valid;
};

// MEM/WB pipeline register:
struct MEMWB {
    Instruction instr;   // the instruction in write-back
    std::string opcode;
    int         memData;
    int         aluResult;
    int         writeReg;
    bool        valid;
};

#endif // PIPELINEREGS_H
