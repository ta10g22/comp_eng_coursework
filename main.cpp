#include <iostream>
#include <fstream>
#include <string>
#include "parser.h"

bool ProgramFetch(std::string &filename ,Parser &parser);
//std::string ProgramStore(std::string name);




int main (){
    std::string ProgramName;
    int CycleCount = 1; // this keeps track of the current cycle
    bool SimulationComplete =1;

    std::string Filename;
    std::cout << "input the name of the file you will like to simulate" << std::endl;
    std::cin >> Filename ;

    // This function uses the file name to extract the data from it and send it to the parser
     if (ProgramFetch(Filename ,parser)) {
        std::cout << "File has been read!"
     }
//   ProgramStore(ProgramName);
    
    
/*
    if(){
        SimulationComplete =1;

    }
    else{
        SimulationComplete = 0;
    }
*/

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

    //Total program simualation results
    std::cout << "Total number of instructions issued by the program: " << Totalinstructionsissued << std::endl;
    std::cout << "Total number of instructions executed: " << Totalinstructionsexecuted << std::endl;
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
;l'
        }

        file.close();
        return 0;
    }
}


/*
std::string ProgramStore(std::string name){

}
*/


/*
    limited instruction set:
    add
    subtract
    loadword
    storeword
    branch (beq)




    if extra time :
    and
    or
    jump

*/