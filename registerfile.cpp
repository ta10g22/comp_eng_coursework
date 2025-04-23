#include "registerfile.h"
#include <iostream>
#include <iomanip>


// Index 0 is the hard‑wired constant $zero (always reads 0, writes are ignored).


RegisterFile::RegisterFile() {
    for (int i = 0; i < 32; ++i) {
        m_regs[i] = 0;
    }
}

int RegisterFile::read(int regNum) const {
    if (regNum < 0 || regNum >= 32) {
        std::cerr << "Register read error: out-of-range regNum " << regNum << std::endl;
        return 0;
    }
    return m_regs[regNum];
}

void RegisterFile::write(int regNum, int value) {
    if (regNum == 0) return; // $zero is always 0
    if (regNum < 0 || regNum >= 32) {
        std::cerr << "Register write error: out-of-range regNum " << regNum << std::endl;
        return;
    }
    m_regs[regNum] = value;
}

void RegisterFile::dump() const {
    std::cout << "--- Register file values ---\n";
    for (int i = 0; i < 32; ++i) {
        std::cout << "$" << std::setw(2) << std::left << i << ": " << std::setw(6) << m_regs[i];
        if (i % 4 == 3) std::cout << "\n";
        else std::cout << "\t";
    }
    std::cout << "-----------------------------\n";
}