#include "Kernel.h"

#include <iomanip>
#include <stdexcept>

/*
Name: Tonne Charles
Class: CMPS 2143
Assignment: Program 4 - Color, Kernels, and Convolution
Description: Implements convolution kernels and named kernel factories.
*/

Kernel::Kernel(int size) {
    if (size < 3 || size % 2 == 0) {
        throw std::invalid_argument("Kernel size must be odd and at least 3.");
    }

    size_ = size;
    data_ = std::vector<std::vector<double>>(size_, std::vector<double>(size_, 0.0));
}

Kernel::Kernel(int size, const std::vector<double>& values) {
    if (size < 3 || size % 2 == 0) {
        throw std::invalid_argument("Kernel size must be odd and at least 3.");
    }

    if (static_cast<int>(values.size()) != size * size) {
        throw std::invalid_argument("Kernel values must equal size * size.");
    }

    size_ = size;
    data_ = std::vector<std::vector<double>>(size_, std::vector<double>(size_, 0.0));

    for (int row = 0; row < size_; row++) {
        for (int col = 0; col < size_; col++) {
            data_[row][col] = values[row * size_ + col];
        }
    }
}

double& Kernel::at(int row, int col) {
    if (row < 0 || row >= size_ || col < 0 || col >= size_) {
        throw std::out_of_range("Kernel index out of range.");
    }

    return data_[row][col];
}

const double& Kernel::at(int row, int col) const {
    if (row < 0 || row >= size_ || col < 0 || col >= size_) {
        throw std::out_of_range("Kernel index out of range.");
    }

    return data_[row][col];
}

int Kernel::size() const {
    return size_;
}

Kernel Kernel::identity() {
    return Kernel(3, {
        0, 0, 0,
        0, 1, 0,
        0, 0, 0
    });
}

Kernel Kernel::boxBlur() {
    return Kernel(3, {
        1.0 / 9, 1.0 / 9, 1.0 / 9,
        1.0 / 9, 1.0 / 9, 1.0 / 9,
        1.0 / 9, 1.0 / 9, 1.0 / 9
    });
}

Kernel Kernel::sharpen() {
    return Kernel(3, {
         0, -1,  0,
        -1,  5, -1,
         0, -1,  0
    });
}

Kernel Kernel::edgeDetect() {
    return Kernel(3, {
        -1, -1, -1,
        -1,  8, -1,
        -1, -1, -1
    });
}

Kernel Kernel::emboss() {
    return Kernel(3, {
        -2, -1, 0,
        -1,  1, 1,
         0,  1, 2
    });
}

Kernel Kernel::gaussianBlur() {
    return Kernel(3, {
        1.0 / 16, 2.0 / 16, 1.0 / 16,
        2.0 / 16, 4.0 / 16, 2.0 / 16,
        1.0 / 16, 2.0 / 16, 1.0 / 16
    });
}

std::ostream& operator<<(std::ostream& os, const Kernel& k) {
    os << std::fixed << std::setprecision(3);

    for (int row = 0; row < k.size(); row++) {
        os << "[ ";

        for (int col = 0; col < k.size(); col++) {
            os << std::setw(7) << k.at(row, col) << " ";
        }

        os << "]\n";
    }

    return os;
}
