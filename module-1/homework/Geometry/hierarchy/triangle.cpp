#include "triangle.h"
#include <stdexcept>

Circle Triangle::circumscribedCircle() const {
    auto[ax, ay] = vertices[0];
    auto[bx, by] = vertices[1];
    auto[cx, cy] = vertices[2];
    double d = 2 * (ax * (by - cy) + bx * (cy - ay) + cx * (ay - by));
    if (isEq(d, 0)) {
        throw std::logic_error("d == 0");
    }
    double ux = ((ax * ax + ay * ay) * (by - cy)
                 + (bx * bx + by * by) * (cy - ay)
                 + (cx * cx + cy * cy) * (ay - by)) / d;
    double uy = ((ax * ax + ay * ay) * (cx - bx)
                 + (bx * bx + by * by) * (ax - cx)
                 + (cx * cx + cy * cy) * (bx - ax)) / d;
    Point center(ux, uy);
    return Circle(center, Dist(center, vertices[0]));
}

Circle Triangle::inscribedCircle() const {
    double a = Dist(vertices[0], vertices[1]);
    double b = Dist(vertices[1], vertices[2]);
    double c = Dist(vertices[2], vertices[0]);
    if (isEq(a + b + c, 0)) {
        throw std::logic_error("a + b + c == 0");
    }
    double px = (a * vertices[0].x + b * vertices[1].x + c * vertices[2].x) / (a + b + c);
    double py = (a * vertices[0].y + b * vertices[1].y + c * vertices[2].y) / (a + b + c);
    double s = (a + b + c) / 2;
    double area = sqrt(s * (s - a) * (s - b) * (s - c));
    return Circle(Point(px, py), area / s);
}