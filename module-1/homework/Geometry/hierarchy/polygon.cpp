#include "polygon.h"
#include "algorithm"

size_t Polygon::verticesCount() const {
    return vertices.size();
}

std::vector<Point> Polygon::getVertices() const {
    return vertices;
}

bool Polygon::operator==(const Shape &another) const {
    auto other = dynamic_cast<const Polygon *>(&another);
    if (other == nullptr || vertices.size() != other->vertices.size()) return false;
    bool res = true;
    for (size_t i = 0; i < verticesCount() && res; ++i)
        res &= (std::find(other->vertices.begin(), other->vertices.end(), vertices[i]) != other->vertices.end());
    return res;
}

bool Polygon::isConvex() const {
    if (verticesCount() <= 3) return true;
    bool res = true;
    for (size_t i = 0; i < verticesCount(); ++i)
        res &= (std::abs(Angle(vertices[i],
                               vertices[(i + 1) % vertices.size()],
                               vertices[(i + 2) % vertices.size()])) < PI);
    return res;
}

double Polygon::perimeter() const {
    if (verticesCount() <= 1) return 0.0;
    double res = Dist(vertices.front(), vertices.back());
    for (int i = 0; i < verticesCount() - 1; ++i) res += Dist(vertices[i], vertices[i + 1]);
    return res;
};

double Polygon::area() const {
    if (verticesCount() <= 2) return 0.0;
    double res = vertices.back().x * vertices.front().y - vertices.back().y * vertices.front().x;
    for (size_t i = 0; i < verticesCount() - 1; ++i)
        res += vertices[i].x * vertices[i + 1].y - vertices[i].y * vertices[i + 1].x;
    return std::abs(res) / 2;
};

bool Polygon::isCongruentTo(const Shape &another) const {
    auto other = dynamic_cast<const Polygon *>(&another);
    if (other == nullptr || vertices.size() != other->vertices.size()) return false;
    auto res = true;
    std::vector<double> sides;
    sides.reserve(verticesCount());
    std::vector<double> other_sides;
    other_sides.reserve(verticesCount());
    for (size_t i = 0; i < verticesCount(); ++i) {
        sides.push_back(Dist(vertices[i], vertices[(i + 1) % verticesCount()]));
        other_sides.push_back(Dist(other->vertices[i], other->vertices[(i + 1) % verticesCount()]));
    }
    std::sort(sides.begin(), sides.end());
    std::sort(other_sides.begin(), other_sides.end());
    for (size_t i = 0; i < verticesCount() && res; ++i) res &= isEq(sides[i], other_sides[i]);
    return res && isSimilarTo(another);
};

bool Polygon::isSimilarTo(const Shape &another) const {
    auto other = dynamic_cast<const Polygon *>(&another);
    if (other == nullptr || vertices.size() != other->vertices.size()) return false;
    std::vector<double> angles;
    angles.reserve(verticesCount());
    std::vector<double> other_angles;
    other_angles.reserve(verticesCount());
    for (size_t i = 0; i < verticesCount(); ++i) {
        angles.push_back(Angle(vertices[i],
                               vertices[(i + 1) % verticesCount()],
                               vertices[(i + 2) % verticesCount()]));
        other_angles.push_back(Angle(other->vertices[i],
                                     other->vertices[(i + 1) % verticesCount()],
                                     other->vertices[(i + 2) % verticesCount()]));
    }
    std::sort(angles.begin(), angles.end());
    std::sort(other_angles.begin(), other_angles.end());
    bool res = true;
    for (size_t i = 0; i < verticesCount() && res; ++i) res &= isEq(std::abs(angles[i]), std::abs(other_angles[i]));
    return res;
};

bool Polygon::containsPoint(Point point) const {
    double angles = 0.0;
    for (size_t i = 0; i < verticesCount(); ++i) {
        size_t j = (i + 1) % verticesCount();
        double kos = (vertices[j] - vertices[i]) % (point - vertices[i]);
        double scal = (vertices[i] - point) * (vertices[j] - point);
        if (isEq(kos, 0.0) && scal <= 0) {
            return true;
        }
        angles += Angle(point, vertices[i], vertices[j]);
    }
    return (isEq(angles, 2 * PI) || isEq(angles, -2 * PI));
};

void Polygon::rotate(Point center, double angle) {
    angle = angle * (PI / 180);
    for (auto &[x, y] : vertices) {
        double nx = cos(angle) * (x - center.x) - sin(angle) * (y - center.y) + center.x;
        y = sin(angle) * (x - center.x) + cos(angle) * (y - center.y) + center.y;
        x = nx;
    }
};

void Polygon::reflex(Point center) {
    for (auto &[x, y] : vertices) {
        x = -(x - center.x) + center.x;
        y = -(y - center.y) + center.y;
    }
};

void Polygon::reflex(Line axis) {
    double m = (axis.p2.y - axis.p1.y) / (axis.p2.x - axis.p1.x);
    double c = (axis.p1 % axis.p2) / (axis.p2.x - axis.p1.x);
    for (auto &[x, y] : vertices) {
        double d = (x + (y - c) * m) / (1 + m * m);
        x = 2 * d - x;
        y = 2 * d * m - y + 2 * c;
    }
};

void Polygon::scale(Point center, double coefficient) {
    for (auto &[x, y] : vertices) {
        x = (x - center.x) * coefficient + center.x;
        y = (y - center.y) * coefficient + center.y;
    }
};