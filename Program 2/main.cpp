#include "Args.h"
#include <iostream>

/*
 * main
 * ----
 * Calls Args::parse and prints results.
 * Handles errors cleanly.
 */
int main(int argc, char* argv[]) {
    try {
        Args args = Args::parse(argc, argv);

        std::cout << "INPUT  : " << args.input << "\n";
        std::cout << "OUTPUT : " << args.output << "\n";

        std::cout << "FLAGS  : ";
        if (args.grayscale) std::cout << "grayscale ";
        if (args.blur) std::cout << "blur ";
        if (args.flipH) std::cout << "flipH ";
        if (args.flipV) std::cout << "flipV ";
        std::cout << "\n";

        std::cout << "PARAMS : ";
        if (args.use_brighten) std::cout << "brighten=" << args.brighten << " ";
        if (args.use_rotate) std::cout << "rotate=" << args.rotate << " ";
        std::cout << "\n";
    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
        std::cout << "Usage: ./imgtool <input_image> <output_image> [options]\n";
        return 1;
    }

    return 0;
}