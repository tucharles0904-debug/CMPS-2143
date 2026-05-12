#pragma once

#include "Color.h"

#include <iostream>
#include <string>
#include <vector>

class Kernel;

class Image {
public:
    Image(int width, int height);

    static Image load(const std::string& filename);
    void save(const std::string& filename, int jpegQuality = 90) const;

    int width() const;
    int height() const;

    std::vector<Color>& operator[](int row);
    const std::vector<Color>& operator[](int row) const;

    std::vector<std::vector<Color>>& pixels();
    const std::vector<std::vector<Color>>& pixels() const;

    Image apply(const Kernel& k) const;

    friend std::ostream& operator<<(std::ostream& os, const Image& img);

private:
    int _width;
    int _height;
    std::vector<std::vector<Color>> _pixels;
};
