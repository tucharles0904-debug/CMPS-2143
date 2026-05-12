#pragma once

#include "Filter.h"

class Rotate : public Filter {
public:
    explicit Rotate(int degrees);

    void apply(Grid& pixels) override;
    std::string name() const override;

private:
    int degrees;
};
