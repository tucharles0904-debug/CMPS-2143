#include "Args.h"

#include <cctype>
#include <cstdlib>
#include <iostream>
#include <string>

void Args::error(const std::string& message) {
    std::cout << "Error: " << message << "\n";
    std::cout << "Usage: ./imgtool <input_image> <output_image> [options]\n";
    std::exit(1);
}

bool Args::isImageFile(const std::string& filename) {
    std::string name = filename;

    for (char& ch : name) {
        ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
    }

    auto endsWith = [&](const std::string& ext) {
        if (name.size() < ext.size()) {
            return false;
        }

        return name.substr(name.size() - ext.size()) == ext;
    };

    return endsWith(".png") ||
           endsWith(".jpg") ||
           endsWith(".jpeg") ||
           endsWith(".bmp") ||
           endsWith(".ppm");
}

bool Args::parseInt(const std::string& text, int& value) {
    try {
        size_t pos = 0;
        value = std::stoi(text, &pos);
        return pos == text.size();
    }
    catch (...) {
        return false;
    }
}

bool Args::startsWithDash(const std::string& text) {
    return !text.empty() && text[0] == '-';
}

Args Args::parse(int argc, char* argv[]) {
    Args args;

    if (argc < 2) {
        error("input file is required");
    }

    if (argc < 3) {
        error("output file is required");
    }

    args.input = argv[1];
    args.output = argv[2];

    if (!isImageFile(args.input)) {
        error("input file must be an image file");
    }

    if (!isImageFile(args.output)) {
        error("output file must be an image file");
    }

    for (int i = 3; i < argc; i++) {
        std::string token = argv[i];

        if (token == "--grayscale" || token == "-g") {
            args.grayscale = true;
        }
        else if (token == "--blur" || token == "-l") {
            args.blur = true;
        }
        else if (token == "--flipH" || token == "-h") {
            args.flipH = true;
        }
        else if (token == "--flipV" || token == "-v") {
            args.flipV = true;
        }
        else if (token.size() > 2 && token[0] == '-' && token[1] != '-') {
            for (int j = 1; j < static_cast<int>(token.size()); j++) {
                if (token[j] == 'g') {
                    args.grayscale = true;
                }
                else if (token[j] == 'l') {
                    args.blur = true;
                }
                else if (token[j] == 'h') {
                    args.flipH = true;
                }
                else if (token[j] == 'v') {
                    args.flipV = true;
                }
                else {
                    error("unknown option '" + token + "'");
                }
            }
        }
        else if (token == "--brighten" || token == "-b") {
            if (i + 1 >= argc) {
                error("'" + token + "' requires an integer value");
            }

            std::string valueText = argv[++i];

            if (startsWithDash(valueText)) {
                int temp = 0;

                if (!parseInt(valueText, temp)) {
                    error("'" + token + "' expected a value but got option '" + valueText + "'");
                }
            }

            int value = 0;

            if (!parseInt(valueText, value)) {
                error("invalid integer for '" + token + "': '" + valueText + "'");
            }

            if (value < -255 || value > 255) {
                error("'" + token + "' must be in [-255, 255]");
            }

            args.use_brighten = true;
            args.brighten = value;
        }
        else if (token.rfind("--brighten=", 0) == 0) {
            std::string valueText = token.substr(11);

            if (valueText.empty()) {
                error("'--brighten' requires an integer value");
            }

            int value = 0;

            if (!parseInt(valueText, value)) {
                error("invalid integer for '--brighten': '" + valueText + "'");
            }

            if (value < -255 || value > 255) {
                error("'--brighten' must be in [-255, 255]");
            }

            args.use_brighten = true;
            args.brighten = value;
        }
        else if (token == "--rotate" || token == "-r") {
            if (i + 1 >= argc) {
                error("'" + token + "' requires an integer value");
            }

            std::string valueText = argv[++i];

            if (startsWithDash(valueText)) {
                int temp = 0;

                if (!parseInt(valueText, temp)) {
                    error("'" + token + "' expected a value but got option '" + valueText + "'");
                }
            }

            int value = 0;

            if (!parseInt(valueText, value)) {
                error("invalid integer for '" + token + "': '" + valueText + "'");
            }

            if (value != 0 && value != 90 && value != 180 && value != 270) {
                error("'" + token + "' must be one of {0, 90, 180, 270}");
            }

            args.use_rotate = true;
            args.rotate = value;
        }
        else if (token.rfind("--rotate=", 0) == 0) {
            std::string valueText = token.substr(9);

            if (valueText.empty()) {
                error("'--rotate' requires an integer value");
            }

            int value = 0;

            if (!parseInt(valueText, value)) {
                error("invalid integer for '--rotate': '" + valueText + "'");
            }

            if (value != 0 && value != 90 && value != 180 && value != 270) {
                error("'--rotate' must be one of {0, 90, 180, 270}");
            }

            args.use_rotate = true;
            args.rotate = value;
        }
        else if (!token.empty() && token[0] == '-') {
            error("unknown option '" + token + "'");
        }
        else {
            error("unexpected argument '" + token + "'");
        }
    }

    return args;
}

void Args::print() const {
    std::cout << "INPUT  : " << input << "\n";
    std::cout << "OUTPUT : " << output << "\n";

    std::cout << "FLAGS  :";

    if (grayscale) std::cout << " grayscale";
    if (blur) std::cout << " blur";
    if (flipH) std::cout << " flipH";
    if (flipV) std::cout << " flipV";

    std::cout << "\n";

    std::cout << "PARAMS :";

    if (use_brighten) std::cout << " brighten=" << brighten;
    if (use_rotate) std::cout << " rotate=" << rotate;

    std::cout << "\n";
}
