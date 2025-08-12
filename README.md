# MIPS Computer Pipeline Simulator

A 5-stage pipelined MIPS processor simulator implemented in C++, supporting a core subset of MIPS instructions.

## 📌 Overview

This project simulates the classic 5-stage MIPS pipeline architecture:
- **IF**: Instruction Fetch  
- **ID**: Instruction Decode  
- **EX**: Execute  
- **MEM**: Memory Access  
- **WB**: Write Back  

It supports the following instruction set: add, sub, addi, lw, sw, beq, j

## ⚙️ Components

- **Parser**: Tokenizes MIPS assembly files and stores them in instruction memory.
- **Instruction Memory**: Stores parsed instructions.
- **Register File**: Simulates 32 general-purpose registers.
- **Data Memory**: Simulates byte-addressable memory.
- **Program Counter (PC)**: Tracks the address of the next instruction.
- **ALU**: Performs arithmetic and comparison operations.
- **Hazard Unit**: Handles load-use hazard detection and data forwarding.
- **Control Unit**: Orchestrates the pipeline stages and manages pipeline registers.

## 🧪 Showcase Program

A custom MIPS assembly program is included to:
- Compute the squares of all integers from 0 to 200
- Store the results in memory
- Demonstrate forwarding, hazard detection, and efficient branching

> Achieved low CPI and minimal stalls via forwarding and careful instruction scheduling.

## 📈 Performance Summary

- **Instructions executed**: 1611  
- **Total cycles**: 2015  
- **Stalls**: 403  
- **Average CPI**: 1.25  

## 🧪 Testing

The simulator includes tests for:
- ALU operations
- Program Counter functionality
- Hazard detection logic
- Instruction parsing/tokenization

## 🖥️ Requirements

- C++11 or later
- Standard C++ compiler (e.g., g++, clang++)

