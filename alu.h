#ifndef alu.h
#define alu.h

class ALU {
    public:
        
        ALU();
    
        int add(int a, int b);

        int subtract(int a, int b); 

        bool branchifequal(int a , int b);
        
    };


#endif 