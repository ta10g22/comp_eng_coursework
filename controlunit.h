#ifndef CONTROLUNIT_H
#define CONTROLUNIT_H

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
