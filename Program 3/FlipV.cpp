#include "FlipV.h"
#include <utility>

/*
Name: Tonne Charles
Class: CMPS 2143
Assignment: Program 3 - Image Filter Pipeline
ID: 10-P03

Description:
Implements the FlipV filter by mirroring the image
top-to-bottom.
*/

void FlipV::apply(Grid& pixels) {
    int height = static_cast<int>(pixels.size());

    for (int row = 0; row < height / 2; ++row) {
        std::swap(pixels[row], pixels[height - 1 - row]);
    }
}

std::string FlipV::name() const {
    return "flipV";
}