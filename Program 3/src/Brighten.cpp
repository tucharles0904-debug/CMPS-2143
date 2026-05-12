#include "Brighten.h"

#include <string>

Brighten::Brighten(int amount) : amount(amount) {}

void Brighten::apply(Grid& pixels) {
    for (auto& row : pixels) {
        for (Pixel& pixel : row) {
            pixel.r += amount;
            pixel.g += amount;
            pixel.b += amount;
        }
    }
}

std::string Brighten::name() const {
    return "brighten(" + std::to_string(amount) + ")";
}
