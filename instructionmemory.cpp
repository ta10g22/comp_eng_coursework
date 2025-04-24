#include "instructionmemory.h"
#include <stdexcept>
#include <iostream>

void InstructionMemory::addInstruction(const Instruction &instr) {
    m_instructions.push_back(instr);
}

Instruction InstructionMemory::fetch(size_t pc) const {
    if (pc >= m_instructions.size()) {
        throw std::out_of_range("Program counter out of range in InstructionMemory::fetch");
    }
    return m_instructions[pc];
}

size_t InstructionMemory::size() const {
    return m_instructions.size();
}

void InstructionMemory::dumpInstructions() const {
    std::cout << "--- Instruction Memory Dump ---\n";
    for (size_t i = 0; i < m_instructions.size(); ++i) {
        const Instruction &instr = m_instructions[i];
        std::cout << i << ": " << instr.opcode;
        if (instr.opcode == "add" || instr.opcode == "sub") {
            std::cout << " $" << instr.rd << ", $" << instr.rs << ", $" << instr.rt;
        } else if (instr.opcode == "addi") {
            std::cout << " $" << instr.rt << ", $" << instr.rs << ", " << instr.immediate;
        } else if (instr.opcode == "lw" || instr.opcode == "sw") {
            std::cout << " $" << instr.rt << ", " << instr.immediate << "($" << instr.rs << ")";
        } else if (instr.opcode == "beq") {
            std::cout << " $" << instr.rs << ", $" << instr.rt << ", " << instr.label;
        } else if (instr.opcode == "j") {
            std::cout << " " << instr.label;
        }
        std::cout << "\n";
    }
    std::cout << "--------------------------------\n";
}
