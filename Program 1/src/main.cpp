#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <cstdlib>
#include <iostream>
#include <string>

#include "stb_image.h"
#include "stb_image_write.h"
#include "termcolor.hpp"

using namespace termcolor;

bool open_file_default_app(const std::string& path) {
#if defined(_WIN32)
    std::string cmd = "start \"\" \"" + path + "\"";
#elif defined(__APPLE__)
    std::string cmd = "open \"" + path + "\"";
#else
    std::string cmd = "xdg-open \"" + path + "\"";
#endif

    return std::system(cmd.c_str()) == 0;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << red << "Usage: "
                  << blue << "./imgtool <input_image> <output_image>\n"
                  << reset;
        return 1;
    }

    std::string inputPath = argv[1];
    std::string outputPath = argv[2];

    int width = 0;
    int height = 0;
    int channels_in_file = 0;

    unsigned char* data = stbi_load(inputPath.c_str(),
                                    &width,
                                    &height,
                                    &channels_in_file,
                                    3);

    if (!data) {
        std::cerr << red << "Failed to load image: "
                  << reset << inputPath << "\n";
        return 1;
    }

    const int channels = 3;
    const int totalPixels = width * height;

    std::cout << cyan << "Loaded image: "
              << reset << width << "x" << height
              << " channels: " << channels << "\n";

    for (int i = 0; i < totalPixels; i++) {
        int idx = i * channels;

        int r = data[idx + 0];
        int g = data[idx + 1];
        int b = data[idx + 2];

        int gray = static_cast<int>(0.299 * r + 0.587 * g + 0.114 * b);

        unsigned char gr = static_cast<unsigned char>(gray);

        data[idx + 0] = gr;
        data[idx + 1] = gr;
        data[idx + 2] = gr;
    }

    if (!stbi_write_png(outputPath.c_str(),
                        width,
                        height,
                        channels,
                        data,
                        width * channels)) {
        std::cerr << red << "Failed to write output image: "
                  << reset << outputPath << "\n";
        stbi_image_free(data);
        return 1;
    }

    stbi_image_free(data);

    std::cout << green << "Saved output to: "
              << yellow << outputPath
              << reset << "\n";

    std::cout << blue << "Opening output in default viewer...\n"
              << reset;

    if (!open_file_default_app(outputPath)) {
        std::cout << yellow << "Warning: could not launch viewer automatically.\n"
                  << reset;
    }

    return 0;
}
