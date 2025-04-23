#include "programcounter.h"

ProgramCounter::ProgramCounter() : m_pc(0) {}  //constructor and initialization list to make program counter start at 0

int ProgramCounter::value() const {
    return m_pc;                    
}

void ProgramCounter::set(int newPC) {
    m_pc = newPC;                     //jump to new byte address
}

void ProgramCounter::step() {
    m_pc += 1;     // next instruction (byte address)
}