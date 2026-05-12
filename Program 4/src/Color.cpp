#include "Color.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <stdexcept>

/*
Name: Tonne Charles
Class: CMPS 2143
Assignment: Program 4 - Color, Kernels, and Convolution
Description: Implements the Color class with constructors, operators,
             named constructors, and indexed RGB channel access.
*/

int Color::clamp(int val) {
    return std::max(0, std::min(255, val));
}

int Color::clampDouble(double val) {
    return clamp(static_cast<int>(std::round(val)));
}

Color::Color() {
    r = 0;
    g = 0;
    b = 0;
}

Color::Color(int red, int green, int blue) {
    r = clamp(red);
    g = clamp(green);
    b = clamp(blue);
}

Color Color::fromRGB(int r, int g, int b) {
    return Color(r, g, b);
}

Color Color::fromHex(const std::string& hex) {
    std::string value = hex;

    // Accept either "#ff8000" or "ff8000".
    if (value.size() == 7 && value[0] == '#') {
        value = value.substr(1);
    }

    if (value.size() != 6) {
        throw std::invalid_argument("Invalid hex color.");
    }

    for (char ch : value) {
        if (!std::isxdigit(static_cast<unsigned char>(ch))) {
            throw std::invalid_argument("Invalid hex color.");
        }
    }

    int red = std::stoi(value.substr(0, 2), nullptr, 16);
    int green = std::stoi(value.substr(2, 2), nullptr, 16);
    int blue = std::stoi(value.substr(4, 2), nullptr, 16);

    return Color(red, green, blue);
}

Color Color::fromHSL(double h, double s, double l) {
    if (h < 0 || h >= 360 || s < 0 || s > 1 || l < 0 || l > 1) {
        throw std::invalid_argument("Invalid HSL values.");
    }

    double c = (1 - std::abs(2 * l - 1)) * s;
    double x = c * (1 - std::abs(std::fmod(h / 60.0, 2) - 1));
    double m = l - (c / 2);

    double r1 = 0;
    double g1 = 0;
    double b1 = 0;

    if (h < 60) {
        r1 = c;
        g1 = x;
        b1 = 0;
    } else if (h < 120) {
        r1 = x;
        g1 = c;
        b1 = 0;
    } else if (h < 180) {
        r1 = 0;
        g1 = c;
        b1 = x;
    } else if (h < 240) {
        r1 = 0;
        g1 = x;
        b1 = c;
    } else if (h < 300) {
        r1 = x;
        g1 = 0;
        b1 = c;
    } else {
        r1 = c;
        g1 = 0;
        b1 = x;
    }

    int red = clampDouble((r1 + m) * 255);
    int green = clampDouble((g1 + m) * 255);
    int blue = clampDouble((b1 + m) * 255);

    return Color(red, green, blue);
}

int& Color::operator[](int index) {
    if (index == 0) {
        return r;
    }
    if (index == 1) {
        return g;
    }
    if (index == 2) {
        return b;
    }

    throw std::out_of_range("Color index out of range.");
}

const int& Color::operator[](int index) const {
    if (index == 0) {
        return r;
    }
    if (index == 1) {
        return g;
    }
    if (index == 2) {
        return b;
    }

    throw std::out_of_range("Color index out of range.");
}

Color Color::operator+(const Color& other) const {
    return Color(r + other.r, g + other.g, b + other.b);
}

Color Color::operator*(double scalar) const {
    return Color(
        clampDouble(r * scalar),
        clampDouble(g * scalar),
        clampDouble(b * scalar)
    );
}

Color operator*(double scalar, const Color& c) {
    return c * scalar;
}

bool Color::operator==(const Color& other) const {
    return r == other.r && g == other.g && b == other.b;
}

bool Color::operator!=(const Color& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Color& c) {
    os << "rgb(" << c.r << ", " << c.g << ", " << c.b << ")";
    return os;
}

std::istream& operator>>(std::istream& is, Color& c) {
    int red;
    int green;
    int blue;

    is >> red >> green >> blue;
    c = Color(red, green, blue);

    return is;
}
