#pragma once

#include <string>

class Args {
public:
    std::string input;
    std::string output;

    bool grayscale = false;
    bool blur = false;
    bool flipH = false;
    bool flipV = false;

    bool use_brighten = false;
    int brighten = 0;

    bool use_rotate = false;
    int rotate = 0;

    static Args parse(int argc, char* argv[]);
    void print() const;

private:
    static void error(const std::string& message);
    static bool isImageFile(const std::string& filename);
    static bool parseInt(const std::string& text, int& value);
    static bool startsWithDash(const std::string& text);
};
