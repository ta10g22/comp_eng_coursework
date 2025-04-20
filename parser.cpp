#include "parser.h"
#include <sstream>    // for std::istringstream
#include <iostream>   // for std::cerr on errors

Parser::Parser(InstructionMemory &instrMem)
  : m_instrMem(instrMem)
{}

// This is called for every line you read from the file.
// It breaks the line into tokens, builds an Instruction,
// and then stores it.
void Parser::parseLine(const std::string &line) {
    // 1) skip empty lines or lines that start with '#'
    if (line.empty() || line[0] == '#') return;

    // 2) turn the line into a stream so we can >> into strings
    std::istringstream iss(line);
    std::string opcode;
    iss >> opcode;               // grabs the first word, e.g. "add"

    Instruction instr;
    instr.opcode = opcode;

    // 3) depending on the opcode, read the right operands
    if (opcode == "add" || opcode == "sub") {
        // R-type: add rd, rs, rt
        std::string rd, rs, rt;
        char comma;              // to swallow the commas
        iss >> rd >> comma >> rs >> comma >> rt;
        instr.rd = registerStringToNumber(rd);
        instr.rs = registerStringToNumber(rs);
        instr.rt = registerStringToNumber(rt);

    } else if (opcode == "lw" || opcode == "sw") {
        // I-type memory: lw rt, offset(rs)
        std::string rt, addr;
        char comma;
        iss >> rt >> comma >> addr;  
        // addr looks like "100($t0)" — split at '('
        auto pos = addr.find('(');
        instr.immediate = std::stoi(addr.substr(0, pos));
        std::string rs = addr.substr(pos+1, addr.find(')') - pos - 1);
        instr.rs = registerStringToNumber(rs);
        instr.rt = registerStringToNumber(rt);

    } else if (opcode == "beq") {
        // I-type branch: beq rs, rt, label
        std::string rs, rt, label;
        char comma;
        iss >> rs >> comma >> rt >> comma >> label;
        instr.rs = registerStringToNumber(rs);
        instr.rt = registerStringToNumber(rt);
        instr.label = label;     // you’ll resolve labels yourself later

    } else {
        std::cerr << "Parser error: unknown opcode '" 
                  << opcode << "'\n";
        return; // skip storing it
    }

    // 4) store it in instruction memory
    m_instrMem.addInstruction(instr);
}

// A very basic example of mapping "$t0" → 8, "$zero" → 0, etc.
// You can expand this as you add more registers.
int Parser::registerStringToNumber(const std::string &reg) {
    if (reg == "$zero") return 0;
    if (reg == "$t0")   return 8;
    if (reg == "$t1")   return 9;
    // …and so on for $t2, $s0, $a0, etc.
    // If you get something unknown, just return 0 or print an error.
    return 0;
}

