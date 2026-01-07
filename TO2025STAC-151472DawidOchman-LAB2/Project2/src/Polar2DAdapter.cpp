#include "../include/Polar2DAdapter.h"

Polar2DAdapter::Polar2DAdapter(Vector2D* v) : srcVector(v) {}

double Polar2DAdapter::abs() const {
    return srcVector->abs();
}

double Polar2DAdapter::getAngle() const {
    return srcVector->getAngle();
}

double Polar2DAdapter::cdot(const IVector* param) const {
    return srcVector->cdot(param);
}

std::vector<double> Polar2DAdapter::getComponents() const {
    return srcVector->getComponents();
}

std::ostream& operator<<(std::ostream& os, const Polar2DAdapter& p) {
    os << "Polar2DAdapter(r=" << std::fixed << std::setprecision(2) << p.abs() 
       << ", angle=" << p.getAngle() << " rad = " 
       << (p.getAngle() * 180.0 / M_PI) << "°)";
    return os;
}