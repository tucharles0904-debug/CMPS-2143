#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "Image.h"
#include "Kernel.h"
#include "stb_image.h"
#include "stb_image_write.h"

#include <algorithm>
#include <cmath>
#include <cctype>
#include <stdexcept>

/*
Name: Tonne Charles
Class: CMPS 2143
Assignment: Program 4 - Color, Kernels, and Convolution
Description: Implements the Image class and non-destructive kernel convolution.
*/

static std::string toLower(const std::string& s) {
    std::string result = s;

    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char ch) {
        return static_cast<char>(std::tolower(ch));
    });

    return result;
}

Image::Image(int width, int height)
    : _width(width), _height(height), _pixels(height, std::vector<Color>(width)) {
}

Image Image::load(const std::string& filename) {
    int width = 0;
    int height = 0;
    int channels = 0;

    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &channels, 3);

    if (!data) {
        throw std::runtime_error("Image::load - cannot read file: " + filename);
    }

    Image img(width, height);

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            int index = (row * width + col) * 3;

            img._pixels[row][col] = Color(
                data[index + 0],
                data[index + 1],
                data[index + 2]
            );
        }
    }

    stbi_image_free(data);

    return img;
}

void Image::save(const std::string& filename, int jpegQuality) const {
    if (_pixels.empty() || _pixels[0].empty()) {
        throw std::runtime_error("Image::save - image has no pixels.");
    }

    // Use the current grid size so rotate filters that swap dimensions save correctly.
    int currentHeight = static_cast<int>(_pixels.size());
    int currentWidth = static_cast<int>(_pixels[0].size());

    std::vector<unsigned char> buffer(currentWidth * currentHeight * 3);

    for (int row = 0; row < currentHeight; row++) {
        for (int col = 0; col < currentWidth; col++) {
            int index = (row * currentWidth + col) * 3;

            buffer[index + 0] = static_cast<unsigned char>(std::clamp(_pixels[row][col][0], 0, 255));
            buffer[index + 1] = static_cast<unsigned char>(std::clamp(_pixels[row][col][1], 0, 255));
            buffer[index + 2] = static_cast<unsigned char>(std::clamp(_pixels[row][col][2], 0, 255));
        }
    }

    size_t dot = filename.rfind('.');
    std::string extension = dot == std::string::npos ? "" : toLower(filename.substr(dot));

    int ok = 0;

    if (extension == ".jpg" || extension == ".jpeg") {
        ok = stbi_write_jpg(filename.c_str(), currentWidth, currentHeight, 3, buffer.data(), jpegQuality);
    } else {
        ok = stbi_write_png(filename.c_str(), currentWidth, currentHeight, 3, buffer.data(), currentWidth * 3);
    }

    if (!ok) {
        throw std::runtime_error("Image::save - cannot write file: " + filename);
    }
}

Image Image::apply(const Kernel& k) const {
    if (_pixels.empty() || _pixels[0].empty()) {
        return *this;
    }

    Image result = *this;

    int currentHeight = static_cast<int>(_pixels.size());
    int currentWidth = static_cast<int>(_pixels[0].size());
    int half = k.size() / 2;

    for (int row = half; row < currentHeight - half; row++) {
        for (int col = half; col < currentWidth - half; col++) {
            for (int ch = 0; ch < 3; ch++) {
                double sum = 0.0;

                for (int kr = 0; kr < k.size(); kr++) {
                    for (int kc = 0; kc < k.size(); kc++) {
                        int sourceRow = row + kr - half;
                        int sourceCol = col + kc - half;

                        sum += k.at(kr, kc) * _pixels[sourceRow][sourceCol][ch];
                    }
                }

                result[row][col][ch] = std::clamp(static_cast<int>(std::round(sum)), 0, 255);
            }
        }
    }

    return result;
}

int Image::width() const {
    if (_pixels.empty()) {
        return 0;
    }

    return static_cast<int>(_pixels[0].size());
}

int Image::height() const {
    return static_cast<int>(_pixels.size());
}

std::vector<Color>& Image::operator[](int row) {
    if (row < 0 || row >= height()) {
        throw std::out_of_range("Image row out of range.");
    }

    return _pixels[row];
}

const std::vector<Color>& Image::operator[](int row) const {
    if (row < 0 || row >= height()) {
        throw std::out_of_range("Image row out of range.");
    }

    return _pixels[row];
}

std::vector<std::vector<Color>>& Image::pixels() {
    return _pixels;
}

const std::vector<std::vector<Color>>& Image::pixels() const {
    return _pixels;
}

std::ostream& operator<<(std::ostream& os, const Image& img) {
    int currentWidth = 0;
    int currentHeight = static_cast<int>(img._pixels.size());

    if (!img._pixels.empty()) {
        currentWidth = static_cast<int>(img._pixels[0].size());
    }

    os << "Image(" << currentWidth << " x " << currentHeight << ", "
       << currentWidth * currentHeight << " pixels)";

    return os;
}
