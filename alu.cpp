#include "alu.h"

    ALU::ALU(){}

    int ALU::add(int a , int b){
        return a + b;
    }

    int ALU::subtract(int a , int b){
        return a - b;
    }

    bool ALU::branchifequal(int a , int b){
        return a == b;
    }

