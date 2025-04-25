#include "parser.h"
#include "instruction.h"
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <vector>
#include <fstream>

// ----------------------------------------------------------------------------
// Trim whitespace from both ends
// ----------------------------------------------------------------------------
static std::string trim(const std::string& s) {
    auto l = s.find_first_not_of(" \t\r\n");
    if (l == std::string::npos) return "";
    auto r = s.find_last_not_of(" \t\r\n");
    return s.substr(l, r - l + 1);
}

// ----------------------------------------------------------------------------
// Remove inline comments (from '#' onwards)
// ----------------------------------------------------------------------------
static std::string stripComment(const std::string& s) {
    auto pos = s.find('#');
    return (pos == std::string::npos) ? s : s.substr(0, pos);
}

Parser::Parser(InstructionMemory& instrMem)
  : m_instrMem(instrMem)
  , m_currentInstrIndex(0)
{}

// ----------------------------------------------------------------------------
// Parse an entire file in two passes:
//  1) scan for labels
//  2) resolve labels and emit instructions
// ----------------------------------------------------------------------------
void Parser::parseFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        std::cerr << "Failed to open '" << filename << "'\n";
        return;
    }

    // read all lines
    std::vector<std::string> lines;
    std::string raw;
    while (std::getline(in, raw)) {
        lines.push_back(raw);
    }

    // 1) first pass: record label → instruction index
    int instrIdx = 0;
    for (auto& rl : lines) {
        std::string content = trim(stripComment(rl));
        if (content.empty()) continue;
        if (content.back() == ':') {
            std::string lbl = content.substr(0, content.size() - 1);
            m_labelMap[lbl] = instrIdx;
        } else {
            ++instrIdx;
        }
    }
    for (auto &p : m_labelMap) {
    std::cerr << "[DEBUG] label '" << p.first
              << "' → instr index " << p.second << "\n";
}

    // 2) second pass: actually parse + emit
    m_currentInstrIndex = 0;
    for (auto& rl : lines) {
        parseLine(rl);
    }
}

// ----------------------------------------------------------------------------
// Parse a single line: if it's a label, record it; otherwise build an Instruction
// ----------------------------------------------------------------------------
void Parser::parseLine(const std::string& line) {
    std::string text = trim(stripComment(line));
    if (text.empty()) return;

    // label definition?
    if (text.back() == ':') {
        std::string lbl = text.substr(0, text.size() - 1);
        m_labelMap[lbl] = m_currentInstrIndex;
        return;
    }

    // split opcode + args
    std::istringstream iss(text);
    std::string opcode;
    iss >> opcode;
    std::string args;
    std::getline(iss, args);
    args = trim(args);

    Instruction instr;
    instr.opcode = opcode;

    // split args by comma
    std::vector<std::string> fields;
    std::istringstream argss(args);
    std::string fld;
    while (std::getline(argss, fld, ',')) {
        fields.push_back(trim(fld));
    }

    // decode different opcodes
    if (opcode == "nop") {
        // nothing to do
    }
    else if (opcode == "add" || opcode == "sub") {
        if (fields.size() != 3) {
            std::cerr << "Parser error: " << opcode << " expects 3 operands\n";
            return;
        }
        instr.rd = registerStringToNumber(fields[0]);
        instr.rs = registerStringToNumber(fields[1]);
        instr.rt = registerStringToNumber(fields[2]);
    }
    else if (opcode == "addi") {
        if (fields.size() != 3) {
            std::cerr << "Parser error: addi expects 3 operands\n";
            return;
        }
        instr.rt        = registerStringToNumber(fields[0]);
        instr.rs        = registerStringToNumber(fields[1]);
        instr.immediate = std::stoi(fields[2]);
    }
    else if (opcode == "lw" || opcode == "sw") {
        if (fields.size() != 2) {
            std::cerr << "Parser error: " << opcode << " expects 2 operands\n";
            return;
        }
        instr.rt = registerStringToNumber(fields[0]);
        // parse offset(base)
        auto p1 = fields[1].find('(');
        auto p2 = fields[1].find(')', p1);
        std::string off  = fields[1].substr(0, p1);
        instr.immediate  = off.empty() ? 0 : std::stoi(trim(off));
        std::string base = fields[1].substr(p1 + 1, p2 - p1 - 1);
        instr.rs = registerStringToNumber(trim(base));
    }
    else if (opcode == "beq") {
        if (fields.size() != 3) {
            std::cerr << "Parser error: beq expects 3 operands\n";
            return;
        }
        instr.rs    = registerStringToNumber(fields[0]);
        instr.rt    = registerStringToNumber(fields[1]);
        instr.label = fields[2];
        auto it = m_labelMap.find(instr.label);
        if (it == m_labelMap.end()) {
            std::cerr << "Parser error: undefined label '" << instr.label << "'\n";
            return;
        }
        instr.immediate = it->second;
    }
    else if (opcode == "j") {
        if (fields.size() != 1) {
            std::cerr << "Parser error: j expects 1 operand\n";
            return;
        }
        instr.label = fields[0];
        auto it = m_labelMap.find(instr.label);
        if (it == m_labelMap.end()) {
            std::cerr << "Parser error: undefined label '" << instr.label << "'\n";
            return;
        }
        instr.immediate = it->second;
    }
    else {
        std::cerr << "Parser error: unknown opcode '" << opcode << "' in line: " << text << "\n";
        return;
    }

    // store the instruction and advance
    m_instrMem.addInstruction(instr);
    ++m_currentInstrIndex;
}

int Parser::registerStringToNumber(const std::string& reg) const {
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
    if (reg == "$gp")   return 28;
    if (reg == "$sp")   return 29;
    if (reg == "$fp")   return 30;
    if (reg == "$ra")   return 31;
    std::cerr << "Parser warning: unknown register '" << reg << "'\n";
    return 0;
}
