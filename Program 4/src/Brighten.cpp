#include "Brighten.h"

/*
Name: Tonne Charles
Class: CMPS 2143
Assignment: Program 4 - Color, Kernels, and Convolution
Description: Brightens the image by adding a value to every channel.
*/

Brighten::Brighten(int amount) {
    this->amount = amount;
}

void Brighten::apply(Grid& pixels) {
    for (auto& row : pixels) {
        for (auto& p : row) {
            p.r += amount;
            p.g += amount;
            p.b += amount;
        }
    }
}

std::string Brighten::name() const {
    return "brighten(" + std::to_string(amount) + ")";
}
