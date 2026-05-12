# Program 4

Name: Tonne Charles  
Class: CMPS 2143  
Assignment: Program 4  
Date: May 12, 2026

## Color Class

For Program 4, the old `Pixel` idea was replaced with a `Color` class.

The `Color` class stores three color values:

```cpp
r
g
b
```

Each value represents red, green, and blue. The class also makes sure the values stay between `0` and `255`, so invalid color values do not break the image.

### Kernel Class

This program also adds a `Kernel` class.

A kernel is a small grid of numbers used to apply image effects. The kernel moves across the image and changes each pixel based on the surrounding pixels.

Some examples of kernel filters are:

- blur
- sharpen
- edge detection
- emboss
- gaussian blur

### Image Apply Function

The `Image::apply()` function applies a kernel to an image.

It loops through the image, looks at the surrounding pixels, multiplies those pixels by the kernel values, and creates a new filtered image.

This is how filters like blur, sharpen, and edge detection are applied.

### Filters Used From Program 3

The Program 3 filters were brought forward into Program 4.

These filters include:

- grayscale
- brighten
- flip horizontal
- flip vertical
- rotate

The Program 4 setup still supports these filters, but now the image uses the new `Color` class.

### Grayscale Formula Chosen

I used the luminance formula:

```txt
gray = 0.299*r + 0.587*g + 0.114*b
```

I chose this formula because it produces a more realistic grayscale image than a simple average. It reflects how the human eye perceives green as brighter than red and blue.

## Example Compile Command

```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic -Iinclude src/*.cpp -o imgtool
```

## Example Commands

```bash
./imgtool images/Hulda.jpg out1.png --grayscale
./imgtool images/Hulda.jpg out2.png --brighten 50 --grayscale
./imgtool images/Hulda.jpg out3.png --grayscale --brighten 50
./imgtool images/Hulda.jpg out4.png --flipH --flipV
./imgtool images/Hulda.jpg out5.png --rotate 90 --grayscale
./imgtool images/Hulda.jpg out6.png --blur
./imgtool images/Hulda.jpg out7.png --sharpen
./imgtool images/Hulda.jpg out8.png --edgeDetect
./imgtool images/Hulda.jpg out9.png --gaussian --sharpen
```

## What I Learned

In this program, I learned how image filters can be created using kernel convolution. I also learned how the `Color` class can make working with RGB values cleaner than handling raw pixel values directly.

This program also helped me understand how filters can be chained together in a pipeline so that multiple effects can be applied to the same image.
