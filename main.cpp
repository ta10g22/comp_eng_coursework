/* Notes 
keep in mind the temporary fix stuff you made for lw & sw instructions
why is the PC member funtion value constant 
why is the program counter headerfile not included in the main file
*/

#include <iostream>
#include <fstream>
#include <string>

#include "parser.h"
#include "instructionmemory.h"
#include "registerfile.h"
#include "datamemory.h"
#include "programcounter.h"
#include "controlunit.h"

bool ProgramFetch(const std::string &filename , Parser &parser) { 
    std::string line;  
    std::ifstream file(filename);
    if(!file.is_open()){
        std::cout << "Error opening file" << std::endl ;
        return false;
    }
    else{
        while(std::getline(file,line)){
            parser.parseLine(line);
        }

        file.close();
        return true;
    }
}


int main (){
     // Instantiation of all modules used
     InstructionMemory instructionmemory;
     Parser            parser(instructionmemory);
     DataMemory        datamemory;
     RegisterFile      registerfile;
     ProgramCounter    pc;
     ControlUnit       cpu(instructionmemory, registerfile, datamemory, pc);

    
   // Load program
   std::cout << "input the name of the mips assembly file you will like to simulate: " << std::endl;
   std::string filename;
   std::cin >> filename;
   if (!ProgramFetch(filename, parser)) return 1;
   std::cout << "Loaded " << instructionmemory.size() << " instructions into memory.\n";

   // Simulation parameters
   int numInstr = instructionmemory.size();
   int totalCycles = numInstr + 4;  // pipeline depth = 5 => flush requires 4 extra cycles
   int stallCount = 0;

   // Run pipeline for enough cycles to process all instructions
   for (int cycle = 1; cycle <= totalCycles; ++cycle) {
    std::cout << "\n[Cycle " << cycle << "] PC = " << pc.value() << std::endl;

    // Measure stall: old PC unchanged after IF indicates stall
    int oldPC = pc.value();
    cpu.UpdateInstructionFetch();
       if (pc.value() == oldPC) {
           ++stallCount;
           std::cout << "  Stall inserted (load-use hazard)" << std::endl;
       }

    cpu.UpdateInstructionDecode();
    cpu.UpdateInstructionExecute();
    cpu.UpdateMemoryAccess();
    cpu.UpdateWriteBack();
    cpu.updatePipelineRegisters();
      
    registerfile.dump(); // Dump register file for observability
   }


    // Final statistics
    int instrIssued = totalCycles - stallCount;
    int instrExecuted = numInstr;  // one per loaded instruction
    double avgCPI = static_cast<double>(totalCycles) / instrExecuted;

    std::cout << "\n=== Simulation Complete ===" << std::endl;
    std::cout << "Total Instructions Issued:  " << instrIssued << std::endl;
    std::cout << "Total Instructions Executed:" << instrExecuted << std::endl;
    std::cout << "Total Cycles:               " << totalCycles << std::endl;
    std::cout << "Total Stalls:               " << stallCount << std::endl;
    std::cout << "Average CPI:                " << avgCPI << std::endl;

    return 0;
}