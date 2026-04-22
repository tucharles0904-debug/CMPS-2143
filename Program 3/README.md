## Program 3 Notes

**Name:** Tonne Charles  
**Class:** CMPS 2433  
**Assignment:** Program 3   
**Date:** APRIL 22, 2026  

### Grayscale Formula Chosen
I used the luminance formula:

gray = 0.299*r + 0.587*g + 0.114*b

I chose this formula because it produces a more realistic grayscale image than a simple average. It reflects how the human eye perceives green as brighter than red and blue.

### Example Commands

```bash
./imgtool images/Hulda.jpg out1.png --grayscale
./imgtool images/Hulda.jpg out2.png --brighten 50 --grayscale
./imgtool images/Hulda.jpg out3.png --grayscale --brighten 50
./imgtool images/Hulda.jpg out4.png --flipH --flipV
./imgtool images/Hulda.jpg out5.png --rotate 90 --grayscale --blur
