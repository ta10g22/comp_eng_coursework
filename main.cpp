#include <iostream>
#include <fstream>
#include <string>
#include "parser.h"

bool ProgramFetch(std::string &filename ,Parser &parser);
//std::string ProgramStore(std::string name);

//global variables



int main (){
    std::string ProgramName;
    int CycleCount = 1; // this keeps track of the current cycle
    bool SimulationComplete =1;

    std::string Filename;
    std::cout << "input the name of the mips assembly file you will like to simulate" << std::endl;
    std::cin >> Filename ;

    // This function uses the file name to extract the data from it and send it to the parser
    programFetch(Filename, parser);

//   ProgramStore(ProgramName);
    


    while (!SimulationComplete) { //while loop keeps running as long as SimulationComplete doesn't go true
        std::cout << "Currnet Cycle Count: " << CycleCount << std::endl ;
/*
        updateWriteBackStage();  
        updateMemoryStage();
        updateExecuteStage();
        updateInstructionDecodeStage();
        updateInstructionFetchStage();

        updatePipelineRegisters();
*/
        CycleCount +=1;

        //simulation results per cycle
        std::cout << "Currnet Cycle Count: " << CycleCount << '\n' ;
        std::cout << "Currnet Cycle Count: " << CycleCount << '\n' ;
        std::cout << "Currnet Cycle Count: " << CycleCount << '\n';
    }

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



bool ProgramFetch(std::string &filename , Parser &parser) { 
    std::string line;  
    std::ifstream file(filename);
    if(!file.is_open()){
        std::cout << "Error opening file" << std::endl ;
    }
    else{
        
        while(std::getline(file,line)){
            Parser.readline(line);

        }

        file.close();
        return 0;
    }
}

