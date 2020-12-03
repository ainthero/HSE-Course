#pragma once

#include "polygon.h"
#include "point.h"
#include "circle.h"


class Triangle : public Polygon {
public:
    Triangle() = default;

    Triangle(const Point &p1, const Point &p2, const Point &p3) : Polygon({p1, p2, p3}) {};


    Circle circumscribedCircle() const;

    Circle inscribedCircle() const;

};