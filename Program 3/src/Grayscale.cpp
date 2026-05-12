#include "Grayscale.h"

void Grayscale::apply(Grid& pixels) {
    for (auto& row : pixels) {
        for (Pixel& pixel : row) {
            int gray = static_cast<int>(
                0.299 * pixel.r +
                0.587 * pixel.g +
                0.114 * pixel.b
            );

            pixel.r = gray;
            pixel.g = gray;
            pixel.b = gray;
        }
    }
}

std::string Grayscale::name() const {
    return "grayscale";
}
