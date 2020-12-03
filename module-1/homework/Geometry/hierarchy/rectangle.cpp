#include "rectangle.h"

Rectangle::Rectangle(const Point &p1, const Point &p2, double ratio) : bottom_right(p1), top_left(p2) {
    double d = Dist(bottom_right, top_left);
    double h = d / sqrt(1 + ratio * ratio);
    double w = sqrt(d * d - h * h);
    Point bottom_left = {top_left.x, top_left.y - h};
    Point top_right = {top_left.x - w, top_left.y};
    vertices = {top_left, bottom_left, bottom_right, top_right};
}

std::pair<Line, Line> Rectangle::diagnols() const {
    return {Line(vertices[0], vertices[2]), Line(vertices[1], vertices[3])};
}

Point Rectangle::center() const {
    return {(vertices[0].x + vertices[2].x) / 2, (vertices[0].y + vertices[2].y) / 2};
}