#pragma once

#include <iostream>
#include <vector>

class Kernel {
public:
    explicit Kernel(int size);
    Kernel(int size, const std::vector<double>& values);

    double& at(int row, int col);
    const double& at(int row, int col) const;

    int size() const;

    static Kernel identity();
    static Kernel boxBlur();
    static Kernel sharpen();
    static Kernel edgeDetect();
    static Kernel emboss();
    static Kernel gaussianBlur();

    friend std::ostream& operator<<(std::ostream& os, const Kernel& k);

private:
    int size_;
    std::vector<std::vector<double>> data_;
};
