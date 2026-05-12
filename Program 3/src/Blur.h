#pragma once

#include "Filter.h"

class Blur : public Filter {
public:
    void apply(Grid& pixels) override;
    std::string name() const override;
};
