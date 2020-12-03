#pragma once

#include "polygon.h"
#include "line.h"
#include "point.h"
#include <utility>

class Rectangle : public Polygon {
protected:
    Point top_left;
    Point bottom_right;
public:
    Rectangle() = default;

    Rectangle(const Point &p1, const Point &p2, double ratio);

    Point center() const;

    std::pair<Line, Line> diagnols() const;
};