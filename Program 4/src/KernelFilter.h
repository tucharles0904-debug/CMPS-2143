#pragma once

#include "Filter.h"
#include "Kernel.h"

#include <string>

class KernelFilter : public Filter {
public:
    KernelFilter(const Kernel& kernel, const std::string& filterName);

    void apply(Grid& pixels) override;
    std::string name() const override;

private:
    Kernel kernel;
    std::string filterName;
};
