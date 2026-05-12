#include "KernelFilter.h"

#include <algorithm>
#include <cmath>

/*
Name: Tonne Charles
Class: CMPS 2143
Assignment: Program 4 - Color, Kernels, and Convolution
Description: Adapts a Kernel so it can be used as a normal pipeline Filter.
*/

KernelFilter::KernelFilter(const Kernel& kernel, const std::string& filterName)
    : kernel(kernel), filterName(filterName) {
}

void KernelFilter::apply(Grid& pixels) {
    if (pixels.empty() || pixels[0].empty()) {
        return;
    }

    Grid original = pixels;
    int height = static_cast<int>(pixels.size());
    int width = static_cast<int>(pixels[0].size());
    int half = kernel.size() / 2;

    for (int row = half; row < height - half; row++) {
        for (int col = half; col < width - half; col++) {
            for (int ch = 0; ch < 3; ch++) {
                double sum = 0.0;

                for (int kr = 0; kr < kernel.size(); kr++) {
                    for (int kc = 0; kc < kernel.size(); kc++) {
                        int sourceRow = row + kr - half;
                        int sourceCol = col + kc - half;

                        sum += kernel.at(kr, kc) * original[sourceRow][sourceCol][ch];
                    }
                }

                pixels[row][col][ch] = std::clamp(static_cast<int>(std::round(sum)), 0, 255);
            }
        }
    }
}

std::string KernelFilter::name() const {
    return filterName;
}
