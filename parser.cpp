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
    
    // after skipping empty or comment lines …
    if (line.back() == ':') {
    // This is a label definition line like "loop:" → skip for now
    // (store it later when you add a symbol‑table step)
    return;
}

    // 2) turn the line into a stream so we can >> into strings
    std::istringstream iss(line);
    std::string opcode;
    iss >> opcode;               // grabs the first word, e.g. "add"

    Instruction instr;
    instr.opcode = opcode;

    //R - TYPE
    if (opcode == "add" || opcode == "sub") {
        // R-type: add rd, rs, rt
        std::string rd, rs, rt;
        char comma;              // to swallow the commas
        iss >> rd >> comma >> rs >> comma >> rt;
        instr.rd = registerStringToNumber(rd);
        instr.rs = registerStringToNumber(rs);
        instr.rt = registerStringToNumber(rt);


        // I -TYPE with offsets stored in immediate added to address in "rs"
    } else if (opcode == "lw" || opcode == "sw") {
        // I-type memory: lw rt, offset(rs)
        std::string rt, addr;
        char comma;
        iss >> rt >> comma >> addr;  
        
        // addr looks like "100($t0)" — split at '('
        auto pos = addr.find('(');

        std::string offsetStr = addr.substr(0, pos);
        instr.immediate = offsetStr.empty() ? 0 : std::stoi(offsetStr);

        std::string rs = addr.substr(pos+1, addr.find(')') - pos - 1);
        instr.rs = registerStringToNumber(rs);
        instr.rt = registerStringToNumber(rt);

        // I-TYPE With values stored in immediate added to value in "rs"
    } else if (opcode == "addi") {
        // I-type: addi rt, rs, immediate
        std::string rt, rs;
        char comma;
        iss >> rt >> comma >> rs >> comma >> instr.immediate;
        instr.rs = registerStringToNumber(rs);
        instr.rt = registerStringToNumber(rt);


    } else if (opcode == "beq" ) {
        // I-type branch: beq rs, rt, label
        std::string rs, rt, label;
        char comma;
        iss >> rs >> comma >> rt >> comma >> label;
        instr.rs = registerStringToNumber(rs);
        instr.rt = registerStringToNumber(rt);
        instr.label = label;     // you’ll resolve labels yourself later
        

    } else if (opcode == "j") { 
        // J-type: J address
        std::string address;
        iss >> address;
        instr.label = address;

        // instr.address = std::stoi(address); // convert string to int

    } else if(opcode == "nop"){
          return;
        
    } else if (opcode == "#") {
        return;  // skip comments that don't start immediately at the beginning of the line 


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

    if (reg == "$at")   return 1;

    if (reg == "$v0")   return 2;
    if (reg == "$v1")   return 3;

    if (reg == "$a0")   return 4;
    if (reg == "$a1")   return 5;
    if (reg == "$a2")   return 6;
    if (reg == "$a3")   return 7;

    if (reg == "$t0")   return 8;
    if (reg == "$t1")   return 9;
    if (reg == "$t2")   return 10;
    if (reg == "$t3")   return 11;
    if (reg == "$t4")   return 12;
    if (reg == "$t5")   return 13;
    if (reg == "$t6")   return 14;
    if (reg == "$t7")   return 15;

    if (reg == "$s0")   return 16;
    if (reg == "$s1")   return 17;
    if (reg == "$s2")   return 18;
    if (reg == "$s3")   return 19;
    if (reg == "$s4")   return 20;
    if (reg == "$s5")   return 21;
    if (reg == "$s6")   return 22;
    if (reg == "$s7")   return 23;

    if (reg == "$t8")   return 24;
    if (reg == "$t9")   return 25;

    if (reg == "$k0")   return 26;
    if (reg == "$k1")   return 27;

    if (reg == "$sp")   return 29;
    if (reg == "$ra")   return 31;
    if (reg == "$gp")   return 28;
    if (reg == "$fp")   return 30;


 

    
    // …and so on for $t2, $s0, $a0, etc.
    // If you get something unknown, just return 0 or print an error.
    return 0;
}

