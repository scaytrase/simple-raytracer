#include "color3.h"

Color3::Color3() {
}

Color3::Color3(float nr, float ng, float nb) {
    r = nr;
    g = ng;
    b = nb;
}

Color3 Color3::operator*(const float &op) const {
    return Color3(r * op, g * op, b * op);
}

Color3 Color3::operator*(const Color3 &op) const {
    return Color3(r * op.r, g * op.g, b * op.b);
}

Color3 Color3::operator/(const float &op) const {
    return Color3(r / op, g / op, b / op);
}

Color3 Color3::operator+(const Color3 &op) const {
    return Color3(r + op.r, g + op.g, b + op.b);
}

Color3 Color3::operator-(const Color3 &op) const {
    return Color3(r - op.r, g - op.g, b - op.b);
}

Color3 &Color3::operator+=(const Color3 &op) {
    *this = *this + op;
    return (*this);
}
//void operator *=(Color3 left, const Color3 & op)
//{
//	left = left * op;
//}
//Color3& operator *=(const float & op)
//{
//	*this = *this * op;
//	return (*this);
//}

bool Color3::operator==(const Color3 &op) const {
    return (r == op.r) && (g == op.g) && (b == op.b);
}

bool Color3::operator!=(const Color3 &op) const {
    return (r != op.r) || (g != op.g) || (b != op.b);
}

void Color3::clamp() {
    if (r > 1) r = 1;
    if (g > 1) g = 1;
    if (b > 1) b = 1;
    if (r < 0) r = 0;
    if (g < 0) g = 0;
    if (b < 0) b = 0;
}



