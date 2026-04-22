#include "Grayscale.h"

/*
Name: Tonne Charles
Class: CMPS 2143
Assignment: Program 3 - Image Filter Pipeline
ID: 10-P03

Description:
Implements the Grayscale filter by converting each pixel
to gray using the luminance formula.
*/

void Grayscale::apply(Grid& pixels) {
    for (auto& row : pixels) {
        for (auto& p : row) {
            int gray = static_cast<int>(0.299 * p.r + 0.587 * p.g + 0.114 * p.b);
            p.r = gray;
            p.g = gray;
            p.b = gray;
        }
    }
}

std::string Grayscale::name() const {
    return "grayscale";
}