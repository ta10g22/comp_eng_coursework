#include "datamemory.h"
#include <iostream>

DataMemory::DataMemory(int words)
  : m_mem(words, 0)   // create a vector called m_mem 'words' amount of elements(indexes) and initialize all elements to 0
{}

int DataMemory::loadWord(int addr) const {
    if (addr % 4 != 0) {    //check that the address for lw instruction is aligned for a word
        std::cerr << "DataMemory load: unaligned address " << addr << '\n';  
        return 0;
    }
    int index = addr / 4;  // gives you the index of the data memory vector
    if (index >= m_mem.size()) {
        std::cerr << "DataMemory load: address out of provided range " << addr << '\n';
        return 0;
    }
    return m_mem[index];
}

void DataMemory::storeWord(int addr, int value) {
    if (addr % 4 != 0) {
        std::cerr << "DataMemory store: unaligned address " << addr << '\n';
        return;
    }
    int index = addr / 4;
    if (index >= m_mem.size()) {
        std::cerr << "DataMemory store: address out of provided range " << addr << '\n';
        return;
    }
    m_mem[index] = value;
}
