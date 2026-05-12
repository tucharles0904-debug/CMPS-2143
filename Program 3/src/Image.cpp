#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "Image.h"
#include "stb_image.h"
#include "stb_image_write.h"

#include <algorithm>
#include <cctype>
#include <stdexcept>

static std::string lowerCase(const std::string& text) {
    std::string result = text;

    for (char& ch : result) {
        ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
    }

    return result;
}

Image::Image(int width, int height) {
    _pixels.resize(height, std::vector<Pixel>(width));
}

Image Image::load(const std::string& filename) {
    int width = 0;
    int height = 0;
    int channels = 0;

    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &channels, 3);

    if (!data) {
        throw std::runtime_error("Could not load image: " + filename);
    }

    Image img(width, height);

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            int index = (row * width + col) * 3;

            img[row][col] = Pixel(
                data[index],
                data[index + 1],
                data[index + 2]
            );
        }
    }

    stbi_image_free(data);

    return img;
}

void Image::save(const std::string& filename, int jpegQuality) const {
    int h = height();
    int w = width();

    std::vector<unsigned char> data(w * h * 3);

    for (int row = 0; row < h; row++) {
        for (int col = 0; col < w; col++) {
            int index = (row * w + col) * 3;

            data[index] = static_cast<unsigned char>(std::clamp(_pixels[row][col].r, 0, 255));
            data[index + 1] = static_cast<unsigned char>(std::clamp(_pixels[row][col].g, 0, 255));
            data[index + 2] = static_cast<unsigned char>(std::clamp(_pixels[row][col].b, 0, 255));
        }
    }

    std::string ext = "";
    size_t dot = filename.rfind('.');

    if (dot != std::string::npos) {
        ext = lowerCase(filename.substr(dot));
    }

    int ok = 0;

    if (ext == ".jpg" || ext == ".jpeg") {
        ok = stbi_write_jpg(filename.c_str(), w, h, 3, data.data(), jpegQuality);
    }
    else {
        ok = stbi_write_png(filename.c_str(), w, h, 3, data.data(), w * 3);
    }

    if (!ok) {
        throw std::runtime_error("Could not save image: " + filename);
    }
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

std::vector<Pixel>& Image::operator[](int row) {
    return _pixels[row];
}

const std::vector<Pixel>& Image::operator[](int row) const {
    return _pixels[row];
}

std::vector<std::vector<Pixel>>& Image::pixels() {
    return _pixels;
}

const std::vector<std::vector<Pixel>>& Image::pixels() const {
    return _pixels;
}

std::ostream& operator<<(std::ostream& os, const Image& img) {
    return os << "Image(" << img.width() << " x " << img.height()
              << ", " << img.width() * img.height() << " pixels)";
}
