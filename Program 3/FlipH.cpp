#include "FlipH.h"
#include <utility>

/*
Name: Tonne Charles
Class: CMPS 2143
Assignment: Program 3 - Image Filter Pipeline
ID: 10-P03

Description:
Implements the FlipH filter by mirroring the image
left-to-right.
*/

void FlipH::apply(Grid& pixels) {
    for (auto& row : pixels) {
        int width = static_cast<int>(row.size());

        for (int col = 0; col < width / 2; ++col) {
            std::swap(row[col], row[width - 1 - col]);
        }
    }
}

std::string FlipH::name() const {
    return "flipH";
}
