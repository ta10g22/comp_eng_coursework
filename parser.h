#ifndef PARSER_H
#define PARSER_H

#include <string>
#include "instructionmemory.h"


// The Parser reads lines of MIPS-like assembly, converts them into
// Instruction objects, and stores them in InstructionMemory.
class Parser {
    public:
        // Construct with a reference to the instruction memory to fill
        explicit Parser(InstructionMemory& instrMem);
    
        // Parse a single line of assembly text
        void parseLine(const std::string& line);
    
    private:
        // Map register names (e.g., "$t0") to numbers (0–31)
        int registerStringToNumber(const std::string& reg) const;
    
        InstructionMemory& m_instrMem;
    };
    
    #endif // PARSER_H
    