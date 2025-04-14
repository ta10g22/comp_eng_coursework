#include "datamemory.h"

    DataMemory::DataMemory(){}

    int DataMemory::add(int a , int b){
        int result = a + b;
        return result;
    }

    int DataMemory::subtract(int a , int b){
        int result = a - b;
        return result;
    }

    bool DataMemory::branchifequal(int a , int b){
        int result;
        if (a == b){
            bool result = 0; // if equal the alu sets the zero flag for the control unit to branch
        }
        else{
            bool result = 1;
        }
        return result;
    }

