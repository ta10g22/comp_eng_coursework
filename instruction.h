#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>

// Represents a single parsed instruction.
struct Instruction {
    std::string opcode;   // e.g., "add", "lw", "beq"
    int rd;               // destination register (for R-type)
    int rs;               // source register 1
    int rt;               // source register 2 or target register (for I-type)
    int immediate;        // immediate value or offset
    std::string label;    // branch or jump label (if any)

    // Default constructor initializes fields to safe defaults
    Instruction()
      : opcode(""), rd(0), rs(0), rt(0), immediate(0), label("") {}
};

#endif // INSTRUCTION_H
