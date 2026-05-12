#include "FlipV.h"

#include <algorithm>

void FlipV::apply(Grid& pixels) {
    int height = static_cast<int>(pixels.size());

    for (int row = 0; row < height / 2; row++) {
        std::swap(pixels[row], pixels[height - 1 - row]);
    }
}

std::string FlipV::name() const {
    return "flipV";
}
