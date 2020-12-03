#pragma once

#include "ellipse.h"

class Circle : public Ellipse {
public:
    Circle() = default;

    Circle(const Point &center, double radius) : Ellipse(center, center, 2 * radius) {};

    double radius() const;
};