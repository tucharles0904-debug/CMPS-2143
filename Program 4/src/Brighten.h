#pragma once

#include "Filter.h"

class Brighten : public Filter {
public:
    explicit Brighten(int amount);

    void apply(Grid& pixels) override;
    std::string name() const override;

private:
    int amount;
};
