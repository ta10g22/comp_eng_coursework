#include "parser.h"
#include "instructionmemory.h"
#include <sstream>


Parser::Parser(){}

void Parser::readline(const std::string &line){


}


class instruction {
    public:
    std::string opcode;
    int rd, rs, rt;
    int immediate;
    int address;

};