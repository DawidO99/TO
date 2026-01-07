#include "../include/Polar2D.h"

Polar2D::Polar2D(double r, double angle) : r(r), angle(angle) {}

double Polar2D::getAngle() const {
    return angle;
}

double Polar2D::abs() const {
    return r;
}

Vector2D Polar2D::toVector2D() const {
    return Vector2D(r * cos(angle), r * sin(angle));
}

std::ostream& operator<<(std::ostream& os, const Polar2D& p) {
    os << "Polar2D(r=" << std::fixed << std::setprecision(2) << p.r 
       << ", angle=" << p.angle << " rad = " 
       << (p.angle * 180.0 / M_PI) << "°)";
    return os;
}