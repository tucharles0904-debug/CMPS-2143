# Program 2: Command Line Args Parser

**Name:** Tonne Charles  
**Class:** CMPS 2433  
**Assignment ID:** 07-P02  
**Date:** March 20, 2026  

## Description
This program parses command-line arguments for an image processing tool called `imgtool`. It reads the required input and output filenames, parses optional flags and options, validates all user input, and prints a summary of the final configuration.

This assignment focuses on:
- reading `argc` and `argv`
- handling strings
- validating command-line input
- packaging the parser into a clean, reusable C++ class

## Files

| # | File     | Description |
|---|----------|-------------|
| 1 | `main.cpp` | Calls the parser and prints the formatted output |
| 2 | `Args.h`   | Defines the `Args` class and its data members |
| 3 | `Args.cpp` | Implements parsing logic and validation rules |
| 4 | `README.md` | Explains how to build, run, and test the program |

## Build Instructions
Keep all files in the same folder. Open a terminal in that folder and compile with:

```bash
g++ -std=c++17 -Wall -Wextra -O2 main.cpp Args.cpp -o imgtool
