#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <unordered_map>
#include "instructionmemory.h"

// The Parser reads MIPS-like assembly (with labels, branches, jumps),
// resolves label addresses, and stores the resulting Instructions
// into InstructionMemory.
class Parser {
public:
    // Construct with a reference to the instruction memory to fill
    explicit Parser(InstructionMemory& instrMem);

    // Parse a whole source file (two-pass):
    //  1) Scan for labels
    //  2) Resolve labels and emit instructions
    void parseFile(const std::string& filename);

    // Parse a single line (label or instruction)
    void parseLine(const std::string& line);

private:
    // Map register names ("$t0", etc.) to numbers (0–31)
    int registerStringToNumber(const std::string& reg) const;

    InstructionMemory&                  m_instrMem;
    std::unordered_map<std::string,int> m_labelMap;
    int                                 m_currentInstrIndex;
};

#endif // PARSER_H

    