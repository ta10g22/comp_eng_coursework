#ifndef instructionmemory.h
#define instructionmemory.h

class InstructionMemory {
    public:
        
        InstructionMemory();
    
        int add(int a, int b);

        int subtract(int a, int b); 

        bool branchifequal(int a , int b);
        
    };

#endif