/* Notes 
keep in mind the temporary fix stuff you made for lw & sw instructions

*/
#include <iostream>
#include <fstream>
#include <string>
#include "parser.h"
#include "instructionmemory.h"

bool ProgramFetch(const std::string &filename ,Parser &parser);
//std::string ProgramStore(std::string name);

//global variables


int main (){
    InstructionMemory instructionMemory1;
    Parser parser(instructionMemory1);
    std::string ProgramName;
    int CycleCount = 1; // this keeps track of the current cycle
    bool SimulationComplete =1;

    std::string Filename;
    std::cout << "input the name of the mips assembly file you will like to simulate" << std::endl;
    std::cin >> Filename ;

    // This function uses the file name to extract the data from it and send it to the parser
    bool Fetchstatus = ProgramFetch(Filename, parser);
    if (Fetchstatus) {
        std::cout << "The program has been loaded into memory" << std::endl;
    } else if (Fetchstatus == false) {
        std::cout << "The program was not loaded into memory" << std::endl;
        
    }
//   ProgramStore(ProgramName);
    


 /*   while (!SimulationComplete) { //while loop keeps running as long as SimulationComplete doesn't go true
        std::cout << "Currnet Cycle Count: " << CycleCount << std::endl ;

        updateWriteBackStage();  
        updateMemoryStage();
        updateExecuteStage();
        updateInstructionDecodeStage();
        updateInstructionFetchStage();

        updatePipelineRegisters();

        CycleCount +=1;

        //simulation results per cycle
        std::cout << "Currnet Cycle Count: " << CycleCount << '\n' ;
        std::cout << "Currnet Cycle Count: " << CycleCount << '\n' ;
        std::cout << "Currnet Cycle Count: " << CycleCount << '\n';
    }
        
*/

std::cout << "Loaded " << instructionMemory1.size()
<< " instructions\n";


    int Totalinstructionsissued;
    int Totalinstructionsexecuted;
    int AverageCPI = Totalinstructionsexecuted/CycleCount ;
    int TotalStalls; // Placeholder for stall count


    
    //Total program simualation results
    std::cout << "Total number of instructions issued by the program: " << Totalinstructionsissued << std::endl;
    std::cout << "Total number of instructions executed: " << Totalinstructionsexecuted << std::endl;
    std::cout << "Total number of cycles: " << CycleCount << std::endl;
    std::cout << "Total number of stalls: " << TotalStalls << std::endl; 
    std::cout << "Average Cycle per instruction(CPI): " << AverageCPI << std::endl;
    std::cout << "Program Finsished!" << std::endl;


    return 0;
}



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

