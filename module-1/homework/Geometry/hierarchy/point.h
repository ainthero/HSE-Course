#pragma once

#include <cmath>

const double PI = 3.1415926;
const double EPS = 0.000001;


struct Point {
    double x = 0.0;
    double y = 0.0;

    Point() = default;

    Point(double x, double y) : x(x), y(y) {}

    Point &operator=(const Point &p) = default;

    bool operator==(const Point &p) const;

    bool operator!=(const Point &p) const;

    Point operator+(const Point &p) const;

    Point operator-(const Point &p) const;

    double operator%(const Point &p) const;

    double operator*(const Point &p) const;

    Point operator*(double k) const;

    double Length() const;
};

bool isEq(double lhs, double rhs);

double Angle(const Point &p1, const Point &p2);

double Angle(Point p12, Point p1, Point p2);

double Dist(const Point &p1, const Point &p2);