#ifndef REGISTERFILE_H
#define REGISTERFILE_H 

#include <array>



class RegisterFile {
public:
    RegisterFile();  // constructor should set all registers to 0

    // Read a value stored in register reg(0‑31).  
    int read(int reg) const;

    // Write a'value' into register 'reg'.
    void write(int reg, int value);

    // function that will display whats stored in all registers.
    void dump() const;

private:
    std::array<int, 32> m_regs;    //The std::array has useful methods like fill() and size() so prefer over m_regs[32]
};

#endif 
