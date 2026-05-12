#pragma once

#include "Filter.h"

class Rotate : public Filter {
public:
    explicit Rotate(int angle);

    void apply(Grid& pixels) override;
    std::string name() const override;

private:
    int angle;
};
