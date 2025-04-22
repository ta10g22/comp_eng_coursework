#ifndef PROGRAMCOUNTER_H
#define PROGRAMCOUNTER_H

#include <cstddef>  

class ProgramCounter {
public:
    ProgramCounter();         //constructor so that PC starts at 0
    int value() const;        // read the current PC
    void set(int newPC);      // jump / branch
    void step();                      // PC = PC + 4  (next instruction)

private:
    int m_pc;                 //interger byte address value for the program counter (0,4,8,12, etc)
};

#endif 