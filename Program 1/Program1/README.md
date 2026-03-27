# Program 1 - Image Viewer

**Name:** Tonne Charles  
**Class:** CMPS 2433  
**Assignment:** Program 1 - Image Viewer  
**ID:** 06-P01  
**Date:** March 9, 2026  

## Description
This program loads an image, converts it to grayscale, saves it as a PNG file, and opens the output image using the system’s default viewer. It also uses termcolor to display colored terminal messages.

## Files
- `source1.cpp`
- `stb_image.h`
- `stb_image_write.h`
- `termcolor.hpp`

## Build
```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic source1.cpp -o imgtool
