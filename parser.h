#ifndef PARSER_H
#define PARSER_H


#include <string>
#include "instructionmemory.h"   // So we can call InstructionMemory::addInstruction
#include "instruction.h"         // Holds our Instruction struct

// A very simple Parser class.
// It takes each line of text, turns it into an Instruction,
// and immediately pushes that Instruction into InstructionMemory.
class Parser {
public:
    // Constructor: we give the parser a reference to your InstructionMemory
    Parser(InstructionMemory &instrMem);

    // Called once per line of text
    void parseLine(const std::string &line);

private:
    InstructionMemory &m_instrMem; 

    // Helper to turn strings like "$t0" into numbers like 8
    int registerStringToNumber(const std::string &reg);
};

#endif // PARSER_H
