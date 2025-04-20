#ifndef controlunit.h
#define controlunit.h

class ControlUnit {
    public:
        
        ControlUnit();
    
        int UpdateInstrucionFetch();
        int UpdateInstructionDecode();
        int UpdateInstructionExecute();
        int UpdateMemoryAccess();
        int UpdateWriteBack();
    };



#endif
