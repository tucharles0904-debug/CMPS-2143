#include "Rotate.h"

#include <stdexcept>
#include <string>

Rotate::Rotate(int degrees) : degrees(degrees) {
    if (degrees != 0 && degrees != 90 && degrees != 180 && degrees != 270) {
        throw std::runtime_error("Rotate must be 0, 90, 180, or 270.");
    }
}

void Rotate::apply(Grid& pixels) {
    if (pixels.empty() || pixels[0].empty() || degrees == 0) {
        return;
    }

    int height = static_cast<int>(pixels.size());
    int width = static_cast<int>(pixels[0].size());

    Grid result;

    if (degrees == 90) {
        result.resize(width, std::vector<Pixel>(height));

        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                result[col][height - 1 - row] = pixels[row][col];
            }
        }
    }
    else if (degrees == 180) {
        result.resize(height, std::vector<Pixel>(width));

        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                result[height - 1 - row][width - 1 - col] = pixels[row][col];
            }
        }
    }
    else {
        result.resize(width, std::vector<Pixel>(height));

        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                result[width - 1 - col][row] = pixels[row][col];
            }
        }
    }

    pixels = result;
}

std::string Rotate::name() const {
    return "rotate(" + std::to_string(degrees) + ")";
}
