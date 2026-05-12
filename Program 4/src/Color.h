#pragma once

#include <iostream>
#include <string>

class Color {
public:
    // Constructors
    Color();
    Color(int r, int g, int b);

    // Static factories
    static Color fromRGB(int r, int g, int b);
    static Color fromHex(const std::string& hex);
    static Color fromHSL(double h, double s, double l);

    // Channel access by index: 0 = r, 1 = g, 2 = b
    int& operator[](int index);
    const int& operator[](int index) const;

    // Arithmetic
    Color operator+(const Color& other) const;
    Color operator*(double scalar) const;
    friend Color operator*(double scalar, const Color& c);

    // Comparison
    bool operator==(const Color& other) const;
    bool operator!=(const Color& other) const;

    // I/O
    friend std::ostream& operator<<(std::ostream& os, const Color& c);
    friend std::istream& operator>>(std::istream& is, Color& c);

    // Public channels so the Program 3 filter code still works.
    int r;
    int g;
    int b;

private:
    static int clamp(int val);
    static int clampDouble(double val);
};
