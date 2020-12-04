#include "square.h"

Circle Square::inscribedCircle() const {
    Point center = (bottom_right + top_left) * 0.5;
    return Circle(center, std::abs(bottom_right.y - top_left.y) * 2);
}

Circle Square::circumscribedCircle() const {
    Point center = (bottom_right + top_left) * 0.5;
    return Circle(center, Dist(center, bottom_right));
}