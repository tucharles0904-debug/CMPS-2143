#pragma once

#include "Color.h"

#include <string>
#include <vector>

// P04 uses Color, but this alias lets old Program 3 Pixel code still compile.
using Pixel = Color;
using Grid = std::vector<std::vector<Color>>;

class Filter {
public:
    virtual ~Filter() = default;
    virtual void apply(Grid& pixels) = 0;
    virtual std::string name() const = 0;
};
