#ifndef registerfile.h
#define registerfile.h

class RegisterFile {
    public:
        
        RegisterFile();
    
        int add(int a, int b);

        int subtract(int a, int b); 

        bool branchifequal(int a , int b);
        
    };


#endif