#ifndef ARGS_H
#define ARGS_H

#include <string>

/*
 * Args
 * ----
 * This class represents the parsed command-line arguments
 * for the imgtool program.
 *
 * It stores:
 * - required positional arguments (input/output files)
 * - flags (boolean switches)
 * - options with values (brighten, rotate)
 *
 * It also provides a static parse() function that:
 * - reads argc/argv
 * - validates input
 * - constructs a fully valid Args object
 */
class Args {
public:
    // Positional arguments
    std::string input;
    std::string output;

    // Flags
    bool grayscale = false;
    bool blur = false;
    bool flipH = false;
    bool flipV = false;

    // Options with values
    bool use_brighten = false;
    int brighten = 0;

    bool use_rotate = false;
    int rotate = 0;

    /*
     * parse
     * -----
     * Static factory method that:
     * - parses command-line arguments
     * - validates correctness
     * - returns a fully initialized Args object
     *
     * Throws std::runtime_error if parsing fails.
     */
    static Args parse(int argc, char* argv[]);
};

#endif