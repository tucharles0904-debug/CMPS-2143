#include "Args.h"
#include <iostream>
#include <stdexcept>
#include <sstream>

/*
 * Helper function:
 * Determines if a string looks like an option (starts with '-')
 */
bool is_option(const std::string& s) {
    return !s.empty() && s[0] == '-';
}

/*
 * Helper function:
 * Converts string to integer safely using std::stoi
 */
int to_int(const std::string& s) {
    try {
        size_t pos;
        int value = std::stoi(s, &pos);

        // Ensure entire string was a valid number
        if (pos != s.size()) {
            throw std::runtime_error("");
        }

        return value;
    } catch (...) {
        throw std::runtime_error("invalid integer: " + s);
    }
}

/*
 * Helper function:
 * Splits "--option=value" into ("--option", "value")
 */
std::pair<std::string, std::string> split_equal(const std::string& s) {
    size_t pos = s.find('=');
    if (pos == std::string::npos) {
        return {s, ""};
    }
    return {s.substr(0, pos), s.substr(pos + 1)};
}

/*
 * parse implementation
 */
Args Args::parse(int argc, char* argv[]) {
    if (argc < 3) {
        throw std::runtime_error("missing required arguments");
    }

    Args args;

    // Required positional arguments
    args.input = argv[1];
    args.output = argv[2];

    for (int i = 3; i < argc; ++i) {
        std::string token = argv[i];

        // Handle --option=value format
        auto [opt, val] = split_equal(token);

        // ---------------- FLAGS ----------------
        if (opt == "--grayscale" || opt == "-g") {
            args.grayscale = true;
        }
        else if (opt == "--blur" || opt == "-l") {
            args.blur = true;
        }
        else if (opt == "--flipH" || opt == "-h") {
            args.flipH = true;
        }
        else if (opt == "--flipV" || opt == "-v") {
            args.flipV = true;
        }

        // ---------------- BRIGHTEN ----------------
        else if (opt == "--brighten" || opt == "-b") {
            args.use_brighten = true;

            if (val.empty()) {
                // value should be next token
                if (i + 1 >= argc) {
                    throw std::runtime_error("--brighten requires a value");
                }

                std::string next = argv[++i];

                if (is_option(next)) {
                    throw std::runtime_error("--brighten expected a value but got option " + next);
                }

                args.brighten = to_int(next);
            } else {
                args.brighten = to_int(val);
            }

            if (args.brighten < -255 || args.brighten > 255) {
                throw std::runtime_error("brighten must be in [-255, 255]");
            }
        }

        // ---------------- ROTATE ----------------
        else if (opt == "--rotate" || opt == "-r") {
            args.use_rotate = true;

            if (val.empty()) {
                if (i + 1 >= argc) {
                    throw std::runtime_error("--rotate requires a value");
                }

                std::string next = argv[++i];

                if (is_option(next)) {
                    throw std::runtime_error("--rotate expected a value but got option " + next);
                }

                args.rotate = to_int(next);
            } else {
                args.rotate = to_int(val);
            }

            if (!(args.rotate == 0 || args.rotate == 90 ||
                  args.rotate == 180 || args.rotate == 270)) {
                throw std::runtime_error("rotate must be one of {0, 90, 180, 270}");
            }
        }

        // ---------------- GROUPED FLAGS (-glhv) ----------------
        else if (token.size() > 1 && token[0] == '-' && token[1] != '-') {
            for (size_t j = 1; j < token.size(); ++j) {
                char c = token[j];

                if (c == 'g') args.grayscale = true;
                else if (c == 'l') args.blur = true;
                else if (c == 'h') args.flipH = true;
                else if (c == 'v') args.flipV = true;
                else {
                    throw std::runtime_error(std::string("unknown flag -") + c);
                }
            }
        }

        // ---------------- UNKNOWN ----------------
        else {
            throw std::runtime_error("unknown option " + token);
        }
    }

    return args;
}