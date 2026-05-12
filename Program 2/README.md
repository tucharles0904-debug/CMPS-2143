# Program 2

Name: T'onne Charles  
Class: CMPS 2143  
Assignment: Program 2  
Date: April 2026

This program is a command line argument parser for an image tool.

The program reads the input file, output file, and any filter options typed on the command line.

## What the Program Checks

The program checks for:

- an input image file
- an output image file
- valid filter flags
- valid integer values for brighten and rotate
- invalid or unknown options

## Supported Options

```txt
--grayscale
--blur
--flipH
--flipV
--brighten <number>
--rotate <degrees>
```

Short options can also be used:

```txt
-g
-l
-h
-v
-b <number>
-r <degrees>
```

## Rotate Values

The rotate option only accepts these values:

```txt
0
90
180
270
```

## Brighten Values

The brighten option accepts values from:

```txt
-255 to 255
```

## Example Compile Command

```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic src/main.cpp src/Args.cpp -o imgtool
```

## Example Commands

```bash
./imgtool images/Hulda.jpg out1.png --grayscale
./imgtool images/Hulda.jpg out2.png --brighten 50
./imgtool images/Hulda.jpg out3.png --rotate 90
./imgtool images/Hulda.jpg out4.png --grayscale --brighten 50 --rotate 90
./imgtool images/Hulda.jpg out5.png -g -b 25 -r 180
```

## Example Error Commands

```bash
./imgtool
./imgtool images/Hulda.jpg
./imgtool images/Hulda.jpg out.png --brighten abc
./imgtool images/Hulda.jpg out.png --rotate 45
./imgtool images/Hulda.jpg out.png --unknown
```

## What I Learned

In this program, I learned how to read command line arguments in C++.

I also learned how to check for errors, validate user input, and store options inside a class.
