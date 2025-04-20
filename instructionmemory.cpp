#include "instructionmemory.h"
#include <stdexcept>

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
