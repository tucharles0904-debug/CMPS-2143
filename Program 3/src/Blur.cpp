#include "Blur.h"

void Blur::apply(Grid& pixels) {
    if (pixels.empty() || pixels[0].empty()) {
        return;
    }

    Grid original = pixels;

    int height = static_cast<int>(pixels.size());
    int width = static_cast<int>(pixels[0].size());

    for (int row = 1; row < height - 1; row++) {
        for (int col = 1; col < width - 1; col++) {
            int r = 0;
            int g = 0;
            int b = 0;

            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    r += original[row + i][col + j].r;
                    g += original[row + i][col + j].g;
                    b += original[row + i][col + j].b;
                }
            }

            pixels[row][col].r = r / 9;
            pixels[row][col].g = g / 9;
            pixels[row][col].b = b / 9;
        }
    }
}

std::string Blur::name() const {
    return "blur";
}
