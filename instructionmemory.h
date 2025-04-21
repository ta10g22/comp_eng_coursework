
#ifndef INSTRUCTIONMEMORY_H
#define INSTRUCTIONMEMORY_H

#include <vector>
#include "instruction.h"

// Stores parsed instructions and provides fetch access by program counter.
class InstructionMemory {
    private:
    std::vector<Instruction> m_instructions;
public:
    // Add a parsed instruction to the end of memory
    void addInstruction(const Instruction &instr);

    // Fetch the instruction at index 'pc'
    Instruction fetch(size_t pc) const;

    // Get the total number of instructions loaded
    size_t size() const;

};

#endif // INSTRUCTIONMEMORY_H
