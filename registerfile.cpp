#include "registerfile.h"

RegisterFile::RegisterFile(){}

int RegisterFile::add(int a , int b){
    int result = a + b;
    return result;
}

int RegisterFile::subtract(int a , int b){
    int result = a - b;
    return result;
}

bool RegisterFile::branchifequal(int a , int b){
    int result;
    if (a == b){
        bool result = 0; // if equal the alu sets the zero flag for the control unit to branch
    }
    else{
        bool result = 1;
    }
    return result;
}
