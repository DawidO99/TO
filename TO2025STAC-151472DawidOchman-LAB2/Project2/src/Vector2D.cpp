#include "../include/Vector2D.h"

Vector2D::Vector2D(double x, double y) : x(x), y(y) {}

std::vector<double> Vector2D::getComponents() const {
    return {x, y};
}

double Vector2D::abs() const {
    return sqrt(x * x + y * y);
}

double Vector2D::cdot(const IVector* param) const {
    std::vector<double> comp = param->getComponents();
    if (comp.size() >= 2) {
        return x * comp[0] + y * comp[1];
    }
    return 0;
}

Vector3D Vector2D::cross(const IVector* param) const {
    std::vector<double> comp = param->getComponents();
    double z1 = 0, z2 = 0;
    if (comp.size() >= 3) {
        z2 = comp[2];
    }

    // Iloczyn wektorowy: [x1, y1, z1] × [x2, y2, z2]
    double cx = y * z2 - z1 * comp[1];
    double cy = z1 * comp[0] - x * z2;
    double cz = x * comp[1] - y * comp[0];

    return Vector3D(cx, cy, cz);
}

double Vector2D::getAngle() const {
    return atan2(y, x);
}

std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
    os << "Vector2D(x=" << std::fixed << std::setprecision(2) << v.x
       << ", y=" << v.y << ")";
    return os;
}
