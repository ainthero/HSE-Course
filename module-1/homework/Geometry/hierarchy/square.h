#pragma once

#include "rectangle.h"
#include "circle.h"

class Square : public Rectangle {
    Square() = default;

    Square(const Point &p1, const Point &p2) : Rectangle(p1, p2, 1) {};

    Circle circumscribedCircle() const;

    Circle inscribedCircle() const;

};