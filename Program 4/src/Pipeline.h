#pragma once

#include "Filter.h"

#include <vector>

class Pipeline {
public:
    Pipeline() = default;
    ~Pipeline();

    void add(Filter* filter);
    void run(Grid& pixels);
    void printSteps() const;

private:
    std::vector<Filter*> filters;
};
