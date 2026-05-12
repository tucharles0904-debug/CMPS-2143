# Program 3

Name: Tonne Charles  
Class: CMPS 2143  
Assignment: Program 3  
Date: April 22, 2026

This program is an image filter tool. It loads an image, applies one or more filters, and saves the new image.

The filters used in this program are:

- grayscale
- brighten
- blur
- flip horizontal
- flip vertical
- rotate

## Grayscale Formula Chosen

I used the luminance formula:

```txt
gray = 0.299*r + 0.587*g + 0.114*b
```

I chose this formula because it gives a better grayscale result than just averaging the red, green, and blue values.

## Filters

### Grayscale

The grayscale filter changes each pixel so the red, green, and blue values are all the same gray value.

### Brighten

The brighten filter adds a number to each red, green, and blue value.

### Blur

The blur filter averages nearby pixels to make the image look smoother.

### FlipH

The flip horizontal filter swaps pixels from left to right.

### FlipV

The flip vertical filter swaps rows from top to bottom.

### Rotate

The rotate filter rotates the image by 90, 180, or 270 degrees.

## Example Compile Command

```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic -isystem include src/main.cpp src/Image.cpp src/Pipeline.cpp src/Grayscale.cpp src/Brighten.cpp src/FlipH.cpp src/FlipV.cpp src/Blur.cpp src/Rotate.cpp src/Args.cpp -o imgtool
```

## Example Commands

```bash
./imgtool images/Hulda.jpg out1.png --grayscale
./imgtool images/Hulda.jpg out2.png --brighten 50 --grayscale
./imgtool images/Hulda.jpg out3.png --grayscale --brighten 50
./imgtool images/Hulda.jpg out4.png --flipH --flipV
./imgtool images/Hulda.jpg out5.png --rotate 90 --grayscale
./imgtool images/Hulda.jpg out6.png --blur
```

## What I Learned

In this program, I learned how to work with image pixels and apply filters by changing RGB values.

I also learned how filters can be added to a pipeline so they run in the same order as the command line arguments.
