#pragma once

#include <iostream>
#include <string>
#include <vector>

struct Pixel {
    int r = 0;
    int g = 0;
    int b = 0;

    Pixel() = default;
    Pixel(int r, int g, int b) : r(r), g(g), b(b) {}
};

inline std::ostream& operator<<(std::ostream& os, const Pixel& p) {
    return os << '(' << p.r << ',' << p.g << ',' << p.b << ')';
}

class Image {
public:
    Image(int width, int height);

    static Image load(const std::string& filename);
    void save(const std::string& filename, int jpegQuality = 90) const;

    int width() const;
    int height() const;

    std::vector<Pixel>& operator[](int row);
    const std::vector<Pixel>& operator[](int row) const;

    std::vector<std::vector<Pixel>>& pixels();
    const std::vector<std::vector<Pixel>>& pixels() const;

    friend std::ostream& operator<<(std::ostream& os, const Image& img);

private:
    std::vector<std::vector<Pixel>> _pixels;
};
