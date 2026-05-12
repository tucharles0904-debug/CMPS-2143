#include "FlipH.h"

#include <algorithm>

void FlipH::apply(Grid& pixels) {
    for (auto& row : pixels) {
        int width = static_cast<int>(row.size());

        for (int col = 0; col < width / 2; col++) {
            std::swap(row[col], row[width - 1 - col]);
        }
    }
}

std::string FlipH::name() const {
    return "flipH";
}
