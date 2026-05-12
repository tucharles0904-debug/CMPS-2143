#pragma once

#include "Image.h"

#include <string>
#include <vector>

using Grid = std::vector<std::vector<Pixel>>;

class Filter {
public:
    virtual void apply(Grid& pixels) = 0;
    virtual std::string name() const = 0;
    virtual ~Filter() = default;
};
