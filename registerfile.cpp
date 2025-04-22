#include "registerfile.h"
#include <iostream>


// Index 0 is the hard‑wired constant $zero (always reads 0, writes are ignored).
RegisterFile::RegisterFile() {
    m_regs.fill(0); // set every register to 0 at start
}

int RegisterFile::read(int reg) const {
    if (reg >= m_regs.size()) {
        std::cerr << "RegisterFile read: invalid register index " << reg << '\n';
        return 0;
    }
    return m_regs[reg];
}

void RegisterFile::write(int reg, int value) {
    if (reg == 0) return;         // can't write to a $zero register
    if (reg >= m_regs.size()) {
        std::cerr << "RegisterFile write: invalid register index " << reg << '\n';
        return;
    }
    m_regs[reg] = value;
}

void RegisterFile::dump() const {
    std::cout << "--- Register file values ---\n";
    for (int i = 0; i < m_regs.size(); ++i) {
        std::cout << 'Register $' << i << ": " << m_regs[i] << ((i % 4 == 3) ? '\n' : '\t'); // tiny bit at the end is for formatting to make it look nice :)
    }
    std::cout << "-----------------------------\n";
}
