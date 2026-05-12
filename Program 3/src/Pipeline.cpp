#include "Pipeline.h"

#include <iostream>

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

    for (int i = 0; i < static_cast<int>(filters.size()); i++) {
        std::cout << filters[i]->name();

        if (i < static_cast<int>(filters.size()) - 1) {
            std::cout << " -> ";
        }
    }

    std::cout << "\n";
}
