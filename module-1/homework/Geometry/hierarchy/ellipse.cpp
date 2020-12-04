#include "ellipse.h"

Ellipse::Ellipse(const Point &focus1, const Point &focus2, double sum) : focus({focus1, focus2}), sum(sum) {
    double focus_distance = Dist(focus1, focus2);
    double c = focus_distance / 2;
    a = (sum - focus_distance) / 2 + c;
    b = sqrt((sum / 2) * (sum / 2) - c * c);
};

bool Ellipse::operator==(const Shape &another) const {
    auto other = dynamic_cast<const Ellipse *>(&another);
    return (focus == other->focus && sum == other->sum);
};

double Ellipse::perimeter() const {
    return 4 * (PI * a * b + (a - b)) / (a + b);
};

double Ellipse::area() const {
    return PI * a * b;
};

std::pair<Point, Point> Ellipse::focuses() const {
    return focus;
}

Point Ellipse::center() const {
    return (focus.first + focus.second) * 0.5;
}

double Ellipse::eccentricity() const {
    return Dist(focus.first, focus.second) / 2 / a;
}

std::pair<Line, Line> Ellipse::directrices() const {
    double c = Dist(focus.first, focus.second) / 2;
    return {Line({-(a * a) / c, 1},
                 {-(a * a) / c, -1}),
            Line({(a * a) / c, 1},
                 {(a * a) / c, -1})};
}

bool Ellipse::isCongruentTo(const Shape &another) const {
    auto other = dynamic_cast<const Ellipse *>(&another);
    if (other == nullptr) return false;
    return isEq(Dist(focus.first, focus.second),
                Dist(other->focus.first, other->focus.second)) &&
           isEq(sum, other->sum);
};

bool Ellipse::isSimilarTo(const Shape &another) const {
    auto other = dynamic_cast<const Ellipse *>(&another);
    if (other == nullptr) return false;
    return isEq(a / other->a, b / other->b);
};

bool Ellipse::containsPoint(Point point) const {
    return Dist(point, focus.first) + Dist(point, focus.second) < sum;
};

void Ellipse::rotate(Point center, double angle) {
    angle = angle * (PI / 180);
    {
        auto &[x, y] = focus.first;
        double nx = cos(angle) * (x - center.x) - sin(angle) * (y - center.y) + center.x;
        y = sin(angle) * (x - center.x) + cos(angle) * (y - center.y) + center.y;
        x = nx;
    }
    {
        auto &[x, y] = focus.second;
        double nx = cos(angle) * (x - center.x) - sin(angle) * (y - center.y) + center.x;
        y = sin(angle) * (x - center.x) + cos(angle) * (y - center.y) + center.y;
        x = nx;
    }
};

void Ellipse::reflex(Point center) {
    {
        auto &[x, y] = focus.first;
        x = -(x - center.x) + center.x;
        y = -(y - center.y) + center.y;
    }
    {
        auto &[x, y] = focus.second;
        x = -(x - center.x) + center.x;
        y = -(y - center.y) + center.y;
    }
};

void Ellipse::reflex(Line axis) {
    double m = (axis.p2.y - axis.p1.y) / (axis.p2.x - axis.p1.x);
    double c_ = (axis.p1 % axis.p2) / (axis.p2.x - axis.p1.x);
    {
        auto &[x, y] = focus.first;
        double d = (x + (y - c_) * m) / (1 + m * m);
        x = 2 * d - x;
        y = 2 * d * m - y + 2 * c_;
    }
    {
        auto &[x, y] = focus.second;
        double d = (x + (y - c_) * m) / (1 + m * m);
        x = 2 * d - x;
        y = 2 * d * m - y + 2 * c_;
    }
};

void Ellipse::scale(Point center, double coefficient) {

    a *= coefficient;
    b *= coefficient;
    focus.first = focus.first * coefficient;
    focus.second = focus.second * coefficient;
    sum = 2 * sqrt((Dist(focus.first, focus.second) / 2) * (Dist(focus.first, focus.second) / 2) + a * a);
};