#include "Pipeline.h"

#include <iostream>

/*
Name: Tonne Charles
Class: CMPS 2143
Assignment: Program 4 - Color, Kernels, and Convolution
Description: Stores filters and applies them in order.
*/

Pipeline::~Pipeline() {
    for (Filter* filter : filters) {
        delete filter;
    }
}

void Pipeline::add(Filter* filter) {
    filters.push_back(filter);
}

void Pipeline::run(Grid& pixels) {
    for (Filter* filter : filters) {
        filter->apply(pixels);
    }
}

void Pipeline::printSteps() const {
    std::cout << "FILTERS : ";

    if (filters.empty()) {
        std::cout << "none";
    }

    for (int i = 0; i < static_cast<int>(filters.size()); i++) {
        std::cout << filters[i]->name();

        if (i < static_cast<int>(filters.size()) - 1) {
            std::cout << " -> ";
        }
    }

    std::cout << "\n";
}
