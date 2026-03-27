# Program 1 - Image Viewer

**Name:** Tonne Charles  
**Class:** CMPS 2433  
**Assignment:** Program 1 - Image Viewer  
**ID:** 06-P01  
**Date:** March 9, 2026  

---

## Description
This program loads an image, converts it to grayscale, and saves it as a PNG file.  
It also displays colored terminal messages using termcolor and automatically opens the output image in the system’s default viewer.

---

## Files
- `source1.cpp` – main program
- `stb_image.h` – image loading library
- `stb_image_write.h` – image writing library
- `termcolor.hpp` – colored terminal output

---

## Build Instructions
Compile the program using:

```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic source1.cpp -o imgtool
