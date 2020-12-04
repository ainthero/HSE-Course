#pragma once

#include "shape.h"
#include <utility>

class Ellipse : public Shape {
protected:
    std::pair<Point, Point> focus;
    double sum = 0.0;
    double a = 0.0;
    double b = 0.0;
public:
    Ellipse() = default;

    Ellipse(const Point &focus1, const Point &focus2, double sum);

    std::pair<Point, Point> focuses() const;

    Point center() const;

    std::pair<Line, Line> directrices() const;

    double eccentricity() const;

    bool operator==(const Shape &another) const override;

    double perimeter() const override;

    double area() const override;

    bool isCongruentTo(const Shape &another) const override;

    bool isSimilarTo(const Shape &another) const override;

    bool containsPoint(Point point) const override;

    void rotate(Point center, double angle) override;

    void reflex(Point center) override;

    void reflex(Line axis) override;

    void scale(Point center, double coefficient) override;


};