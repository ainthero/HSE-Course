#pragma once

#include "shape.h"
#include <utility>
#include <vector>

class Polygon : public Shape {
protected:
    std::vector<Point> vertices;
public:
    Polygon() = default;

    explicit Polygon(std::vector<Point> vertices) : vertices(std::move(vertices)) {};

    bool operator==(const Shape &another) const override;

    size_t verticesCount() const;

    std::vector<Point> getVertices() const;

    bool isConvex() const;

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