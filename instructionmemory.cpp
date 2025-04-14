#include  "instructionmemory.h"

InstructionMemory::InstructionMemory(){}

int InstructionMemory::add(int a , int b){
    int result = a + b;
    return result;
}

int InstructionMemory::subtract(int a , int b){
    int result = a - b;
    return result;
}

bool InstructionMemory::branchifequal(int a , int b){
    int result;
    if (a == b){
        bool result = 0; // if equal the alu sets the zero flag for the control unit to branch
    }
    else{
        bool result = 1;
    }
    return result;
}
