#ifndef ALU_H
#define ALU_H

class ALU {
    public:
        
        ALU();
    
        int add(int a, int b);

        int subtract(int a, int b); 

        bool branchifequal(int a , int b);
        
    };


#endif 