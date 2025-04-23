#ifndef PIPELINEREGS_H
#define PIPELINEREGS_H

#include "instruction.h"
#include <string> // for opcodes

// IF/ID pipeline register:
struct IFID {
    Instruction instr;  // fetched instruction
    int pcPlus1;        // next instruction for branch
    bool valid;         // tell us if the pipeline register holds a proper instruction?
};

// ID/EX pipeline register:
struct IDEX {
    std::string opcode; // operation name
    int rs, rt, rd;     // register indices
    int rsVal, rtVal;   // register values
    int immediate;      // immediate value
    int pcPlus1;        // PC+1 for branches
    bool valid;         // is this register valid?
};

// EX/MEM pipeline register:
struct EXMEM {
    std::string opcode;  // operation name
    int aluResult;       // result from ALU
    int rtVal;           // value to store (SW)
    int writeReg;        // destination register index
    bool branchTaken;    // did we take a branch?
    int branchTarget;    // where to jump if branch is taken
    bool valid;          // is this register valid?
};

// MEM/WB pipeline register:
struct MEMWB {
    std::string opcode;  // operation name
    int memData;         // data loaded from memory
    int aluResult;       // ALU result for R-type/addi
    int writeReg;        // destination register index
    bool valid;          // is this register valid?
};

#endif