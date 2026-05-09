# PE Decompiler (Work in Progress)

## What is this?

This is a beginner reverse engineering project that parses Windows executable files (.exe / .dll) and will eventually become a simple decompiler.

## Current Features

* Reads PE (Portable Executable) files
* Parses headers
* Lists sections
* Detects the `.text` (code) section

## Goal

The goal of this project is to:

* Disassemble machine code into assembly
* Analyze control flow
* Convert assembly into simple pseudo-C code

## Tech

* C++
* Planned: Capstone disassembly engine

## How to Run

1. Open the project in your IDE (Visual Studio / VS Code)
2. Build the project
3. Run the program with a `.exe` file as input

## Note

This is a learning project, not a full replacement for tools like Ghidra or IDA.

## Roadmap

*  Add disassembler
*  Detect functions
*  Build control flow graph
*  Generate pseudo-code

## Author

Zeerakyoungdev (zeerak587-cloud)
