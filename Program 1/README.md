# Program 1

Name: T'onne Charles  
Class: CMPS 2143  
Assignment: Program 1  
Date: March 2026

This program loads an image, converts it to grayscale, saves the new image, and then tries to open the output image automatically.

## What the Program Does

The program does three main things:

- loads an image from the command line
- converts the image to grayscale
- saves the output image as a PNG

It also uses colored terminal output with `termcolor`.

## Grayscale Formula

I used the luminance formula:

```txt
gray = 0.299*r + 0.587*g + 0.114*b
```

This formula gives a better grayscale result because it uses the red, green, and blue values based on how bright they look to the human eye.

## Colored Output

The program uses colored terminal messages for:

- usage message
- failed image loading
- loaded image message
- saved output message
- auto-open warning

## Auto Open

After the image is saved, the program tries to open it with the default image viewer.

It supports:

```txt
Windows
Mac
Linux
```

## Example Compile Command

```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic -Iinclude src/main.cpp -o imgtool
```

## Example Commands

```bash
./imgtool images/Hulda.png output.png
./imgtool images/Hulda.jpg output.png
```

## Example Error Command

```bash
./imgtool
```

## What I Learned

In this program, I learned how to load and save an image in C++.

I also learned how to use command line arguments, add colored terminal output, and open a file with the default viewer after the program finishes.
