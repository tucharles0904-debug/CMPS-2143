## A07 - Program 02 (COMMAND LINE ARGS PARSER)

### T'onne Charles

### Description:

This program parses command-line arguments for an image processing tool called `imgtool`.
It reads input and output filenames, processes flags and options, validates all inputs, and prints a formatted summary of the configuration.

---

### Files

|  #  | File        | Description                                      |
| :-: | ----------- | ------------------------------------------------ |
|  1  | main.cpp    | Calls parser and prints formatted output         |
|  2  | Args.h      | Defines the Args class and data structure        |
|  3  | Args.cpp    | Implements parsing and validation logic          |
| ETC | Other Files | Any additional supporting files (if added later) |

---

### Instructions

- Keep all files in the same folder
- Open terminal in the project directory
- Compile using:

```bash
g++ -std=c++17 -Wall -Wextra -O2 main.cpp Args.cpp -o imgtool
```

- Run using:

```bash
./imgtool <input_image> <output_image> [options]
```
