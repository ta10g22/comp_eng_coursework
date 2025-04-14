#ifndef programcounter.h
#define programcounter.h

class ProgramCounter {
    public:
        
        ProgramCounter();
    
        int add(int a, int b);

        int subtract(int a, int b); 

        bool branchifequal(int a , int b);
        
    };


#endif