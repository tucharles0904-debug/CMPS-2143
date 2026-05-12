// main.cpp - Program 4 driver

#include "Image.h"
#include "Kernel.h"
#include "Pipeline.h"
#include "KernelFilter.h"
#include "Brighten.h"
#include "Grayscale.h"
#include "FlipH.h"
#include "FlipV.h"
#include "Rotate.h"

#include <iostream>
#include <stdexcept>
#include <string>

// Remove the dashes from command line options.
// Example: "--grayscale" becomes "grayscale".
std::string cleanOption(const std::string& option) {
    if (option.rfind("--", 0) == 0) {
        return option.substr(2);
    }

    if (option.rfind("-", 0) == 0) {
        return option.substr(1);
    }

    return option;
}

// Check if the next command line value is another option.
bool isOption(const std::string& value) {
    return value.rfind("-", 0) == 0;
}

// Print a simple help message if the user runs the program wrong.
void printUsage() {
    std::cout << "Usage:\n";
    std::cout << "  ./imgtool input_image output_image [filters]\n\n";
    std::cout << "Examples:\n";
    std::cout << "  ./imgtool images/Hulda.jpg out.png --grayscale\n";
    std::cout << "  ./imgtool images/Hulda.jpg out.png --brighten 50 --sharpen\n";
    std::cout << "  ./imgtool images/Hulda.jpg out.png --flipH --rotate 90\n\n";
    std::cout << "Filters:\n";
    std::cout << "  --grayscale\n";
    std::cout << "  --brighten amount\n";
    std::cout << "  --blur\n";
    std::cout << "  --flipH\n";
    std::cout << "  --flipV\n";
    std::cout << "  --rotate 90|180|270\n";
    std::cout << "  --sharpen\n";
    std::cout << "  --edgeDetect\n";
    std::cout << "  --emboss\n";
    std::cout << "  --gaussian\n";
}

int main(int argc, char* argv[]) {
    try {
        if (argc < 3) {
            printUsage();
            return 1;
        }

        std::string input = argv[1];
        std::string output = argv[2];

        Image img = Image::load(input);
        std::cout << "\nLoaded: " << img << "\n";

        Pipeline pipeline;

        for (int i = 3; i < argc; i++) {
            std::string op = cleanOption(argv[i]);

            if (op == "grayscale") {
                pipeline.add(new Grayscale());
            } else if (op == "brighten") {
                int amount = 25;

                if (i + 1 < argc && !isOption(argv[i + 1])) {
                    amount = std::stoi(argv[i + 1]);
                    i++;
                }

                pipeline.add(new Brighten(amount));
            } else if (op == "blur") {
                pipeline.add(new KernelFilter(Kernel::boxBlur(), "blur"));
            } else if (op == "flipH") {
                pipeline.add(new FlipH());
            } else if (op == "flipV") {
                pipeline.add(new FlipV());
            } else if (op == "rotate") {
                int angle = 90;

                if (i + 1 < argc && !isOption(argv[i + 1])) {
                    angle = std::stoi(argv[i + 1]);
                    i++;
                }

                pipeline.add(new Rotate(angle));
            } else if (op == "sharpen") {
                pipeline.add(new KernelFilter(Kernel::sharpen(), "sharpen"));
            } else if (op == "edgeDetect") {
                pipeline.add(new KernelFilter(Kernel::edgeDetect(), "edgeDetect"));
            } else if (op == "emboss") {
                pipeline.add(new KernelFilter(Kernel::emboss(), "emboss"));
            } else if (op == "gaussian") {
                pipeline.add(new KernelFilter(Kernel::gaussianBlur(), "gaussian"));
            } else {
                throw std::runtime_error("Unknown filter: " + op);
            }
        }

        pipeline.printSteps();
        pipeline.run(img.pixels());

        img.save(output);
        std::cout << "Saved: " << output << "\n";
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << "\n";
        return 1;
    }

    return 0;
}
