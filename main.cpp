#include <iostream>
#include <fstream>
#include <string>

#include "parser.h"
#include "instructionmemory.h"
#include "registerfile.h"
#include "datamemory.h"
#include "programcounter.h"
#include "controlunit.h"

int main() {
    InstructionMemory instructionmemory;
    Parser            parser(instructionmemory);
    DataMemory        datamemory;
    RegisterFile      registerfile;
    ProgramCounter    pc;
    ControlUnit       cpu(instructionmemory, registerfile, datamemory, pc);

    std::cout << "Enter MIPS assembly filename to simulate: ";
    std::string filename;
    std::cin >> filename;

    // Two-pass parse: first build labels, then emit instructions
    parser.parseFile(filename);

    int numInstr = instructionmemory.size();
    std::cout << "Loaded " << numInstr << " instructions.\n";
    instructionmemory.dumpInstructions();

    int retireCount = 0;
    int stallCount = 0;
    int cycle = 1;

    // Run until we've fetched every real instr AND flushed all bubbles
    do {
        std::cout << "\n[Cycle " << cycle << "] PC = " << pc.value() << "\n";

        int oldPC = pc.value();
        cpu.UpdateInstructionFetch();
        if (pc.value() == oldPC) {
            ++stallCount;
            std::cout << "  Stall inserted (load-use hazard)\n";
        }

        cpu.UpdateInstructionDecode();
        cpu.UpdateInstructionExecute();
        cpu.UpdateMemoryAccess();
        retireCount +=cpu.UpdateWriteBack();
        cpu.updatePipelineRegisters();

        registerfile.dump();

        ++cycle;
    }
    while (pc.value() < numInstr || cpu.pipelineNotEmpty());

    int totalCycles   = cycle - 1;
    int instrIssued   = totalCycles - stallCount;
    int instrExecuted = retireCount;
    double avgCPI     = double(totalCycles) / instrExecuted;

    std::cout << "\n=== Simulation Complete ===\n"
              << "Total Cycles:                " << totalCycles   << "\n"
              << "Total Instructions Issued:   " << instrIssued   << "\n"
              << "Total Instructions Executed: " << instrExecuted << "\n"
              << "Total Stalls:                " << stallCount    << "\n"
              << "Average CPI:                 " << avgCPI        << "\n";

    return 0;
}
