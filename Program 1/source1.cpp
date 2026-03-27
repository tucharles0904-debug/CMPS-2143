/*
Name: Tonne Charles
Class: CMPS 2433
Assignment: Program 1 - Image Viewer
ID: 06-P01
Date: March 9, 2026

Description:
This program loads an image, converts it to grayscale,
saves it as a PNG, and opens the output image using
the system’s default image viewer. It also uses colored
terminal output for better user feedback.
*/

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <iostream>
#include <string>
#include <cstdlib>

#include "stb_image.h"
#include "stb_image_write.h"
#include "termcolor.hpp"

using namespace termcolor;

// ------------------------------------------------------------
// Opens file using default system viewer (Windows / Mac / Linux)
// ------------------------------------------------------------
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

// ------------------------------------------------------------
// MAIN PROGRAM
// ------------------------------------------------------------
int main(int argc, char* argv[]) {

    // Check for correct number of arguments
    if (argc < 3) {
        std::cout << red << "Usage: " << blue
                  << "./imgtool <input_image> <output_image>\n"
                  << reset;
        return 1;
    }

    std::string inputPath  = argv[1];
    std::string outputPath = argv[2];

    int width = 0, height = 0, channels_in_file = 0;

    // Load image (force 3 channels: RGB)
    unsigned char* data = stbi_load(inputPath.c_str(),
                                    &width,
                                    &height,
                                    &channels_in_file,
                                    3);

    // Error if image fails to load
    if (!data) {
        std::cerr << red << "Failed to load image: " << reset
                  << inputPath << "\n";
        return 1;
    }

    const int channels = 3;
    const int totalPixels = width * height;

    std::cout << green << "Loaded image: " << reset
              << width << "x" << height
              << " channels: " << channels << "\n";

    // ------------------------------------------------------------
    // Convert image to grayscale using luminance formula
    // ------------------------------------------------------------
    for (int i = 0; i < totalPixels; ++i) {
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

    // Save output image
    if (!stbi_write_png(outputPath.c_str(),
                        width,
                        height,
                        channels,
                        data,
                        width * channels)) {

        std::cerr << red << "Failed to write output image: " << reset
                  << outputPath << "\n";
        stbi_image_free(data);
        return 1;
    }

    stbi_image_free(data);

    std::cout << green << "Saved output to: " << yellow
              << outputPath << reset << "\n";

    // ------------------------------------------------------------
    // Open output image automatically
    // ------------------------------------------------------------
    std::cout << cyan << "Opening output in default viewer...\n" << reset;

    if (!open_file_default_app(outputPath)) {
        std::cout << red << "Warning: could not launch viewer.\n" << reset;
    }

    return 0;
}
