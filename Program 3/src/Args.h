#pragma once

#include <iostream>
#include <string>
#include <vector>

struct Args {
    std::string input;
    std::string output;
    std::vector<std::string> order;
    std::vector<int> brightenAmounts;
    std::vector<int> rotateAngles;

    static Args parse(int argc, char* argv[]);
    void print() const;
};
