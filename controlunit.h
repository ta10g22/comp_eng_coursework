#ifndef controlunit.h
#define controlunit.h

class ControlUnit {
    public:
        
        ControlUnit();
        
        int UpdateInstructionFetch();
        int UpdateInstructionDecode();
        int UpdateInstructionExecute();
        int UpdateMemoryAccess();
        int UpdateWriteBack();
    };



#endif
