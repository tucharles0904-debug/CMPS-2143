#pragma once

#include "Filter.h"

class Grayscale : public Filter {
public:
    void apply(Grid& pixels) override;
    std::string name() const override;
};
