#include "controlunit.h"

    ControlUnit::ControlUnit(){}

    int ControlUnit::add(int a , int b){
        int result = a + b;
        return result;
    }

    int ControlUnit::subtract(int a , int b){
        int result = a - b;
        return result;
    }

    bool ControlUnit::branchifequal(int a , int b){
        int result;
        if (a == b){
            bool result = 0; // if equal the alu sets the zero flag for the control unit to branch
        }
        else{
            bool result = 1;
        }
        return result;
    }

