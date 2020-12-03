#pragma once

#include "point.h"

struct Line {
    Point p1{};
    Point p2{};

    Line() = default;

    Line(const Point &p1, const Point &p2) : p1(p1), p2(p2) {}

    bool operator==(const Line &l);

    bool operator!=(const Line &l);
};