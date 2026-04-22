#include "Rotate.h"

/*
Name: Tonne Charles
Class: CMPS 2143
Assignment: Program 3 - Image Filter Pipeline
ID: 10-P03

Description:
Implements clockwise rotation by 0, 90, 180, or 270 degrees.
Some rotations require building a new grid with swapped
dimensions.
*/

void Rotate::apply(Grid& pixels) {
    if (angle == 0 || pixels.empty() || pixels[0].empty()) {
        return;
    }

    int height = static_cast<int>(pixels.size());
    int width  = static_cast<int>(pixels[0].size());

    if (angle == 180) {
        Grid result(height, std::vector<Pixel>(width));

        for (int row = 0; row < height; ++row) {
            for (int col = 0; col < width; ++col) {
                result[height - 1 - row][width - 1 - col] = pixels[row][col];
            }
        }

        pixels = result;
    }
    else if (angle == 90) {
        Grid result(width, std::vector<Pixel>(height));

        for (int row = 0; row < height; ++row) {
            for (int col = 0; col < width; ++col) {
                result[col][height - 1 - row] = pixels[row][col];
            }
        }

        pixels = result;
    }
    else if (angle == 270) {
        Grid result(width, std::vector<Pixel>(height));

        for (int row = 0; row < height; ++row) {
            for (int col = 0; col < width; ++col) {
                result[width - 1 - col][row] = pixels[row][col];
            }
        }

        pixels = result;
    }
}

std::string Rotate::name() const {
    return "rotate(" + std::to_string(angle) + ")";
}