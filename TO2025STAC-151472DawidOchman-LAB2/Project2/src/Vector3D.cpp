#include "../include/Vector3D.h"

Vector3D::Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}

std::vector<double> Vector3D::getComponents() const {
    return {x, y, z};
}

double Vector3D::abs() const {
    return sqrt(x * x + y * y + z * z);
}

double Vector3D::cdot(const IVector* param) const {
    std::vector<double> comp = param->getComponents();
    double result = x * comp[0] + y * comp[1];
    if (comp.size() >= 3) {
        result += z * comp[2];
    }
    return result;
}

Vector3D Vector3D::cross(const IVector* param) const {
    std::vector<double> comp = param->getComponents();
    double z2 = comp.size() >= 3 ? comp[2] : 0;
    
    // Iloczyn wektorowy metodą macierzową (wyznacznik)
    double cx = y * z2 - z * comp[1];
    double cy = z * comp[0] - x * z2;
    double cz = x * comp[1] - y * comp[0];
    
    return Vector3D(cx, cy, cz);
}

std::ostream& operator<<(std::ostream& os, const Vector3D& v) {
    os << "Vector3D(x=" << std::fixed << std::setprecision(2) << v.x 
       << ", y=" << v.y << ", z=" << v.z << ")";
    return os;
}