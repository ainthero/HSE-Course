#include "point.h"

bool Point::operator==(const Point &p) const {
    return isEq(x, p.x) && isEq(y, p.y);
}

bool Point::operator!=(const Point &p) const {
    return !(*this == p);
}

Point Point::operator+(const Point &p) const {
    return Point{x + p.x, y + p.y};
}

Point Point::operator-(const Point &p) const {
    return Point{x - p.x, y - p.y};
}

double Point::operator%(const Point &p) const {
    return x * p.y - y * p.x;
}

double Point::operator*(const Point &p) const {
    return x * p.x + y * p.y;
}

Point Point::operator*(double k) const {
    return Point{x * k, y * k};
}

double Point::Length() const {
    return sqrt(x * x + y * y);
}

bool isEq(double lhs, double rhs) {
    return std::abs(lhs - rhs) < EPS;
}

double Angle(const Point &p1, const Point &p2) {
    return acos(p1 * p2 / (p1.Length() * p2.Length()));
}

double Angle(Point p12, Point p1, Point p2) {
    p1 = p1 - p12;
    p2 = p2 - p12;
    return atan2(p1 % p2, p1 * p2);
}

double Dist(const Point &p1, const Point &p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}