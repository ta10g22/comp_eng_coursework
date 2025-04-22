#ifndef DATAMEMORY_H
#define DATAMEMORY_H

#include <vector>


// Each element is one 32‑bit word (4 bytes).
// Address 0 -> m_mem[0], address 4 -> m_mem[1], etc.

class DataMemory {
public:
    explicit DataMemory(int words = 1024); //this constructor lets you specify how many words you want ur data memory to have
                                                   //if non is specified is uses 1024 words as default // 4 KB because 1 word = 4 bytes

    // Load a 32‑bit word from byte address 'addr'.
    int loadWord(int addr) const;

    // Store a 32‑bit word passed as 'value' to byte address 'addr'.
    void storeWord(int addr, int value);

    //this fills memory location 'addr' with 'value' before simulation.
    void poke(int addr, int value) 
    { storeWord(addr, value); }

private:
    std::vector<int> m_mem;   // data memory is a vector of integers

};

#endif 
