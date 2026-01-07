#include "../include/Vector3DInheritance.h"

Vector3DInheritance::Vector3DInheritance(const Vector2D& v, double z) 
    : Vector2D(v.getX(), v.getY()), z(z) {}

Vector3DInheritance::Vector3DInheritance(double x, double y, double z) 
    : Vector2D(x, y), z(z) {}

std::vector<double> Vector3DInheritance::getComponents() const {
    return {x, y, z};
}

double Vector3DInheritance::abs() const {
    return sqrt(x * x + y * y + z * z);
}

double Vector3DInheritance::cdot(const IVector* param) const {
    std::vector<double> comp = param->getComponents();
    double result = x * comp[0] + y * comp[1];
    if (comp.size() >= 3) {
        result += z * comp[2];
    }
    return result;
}

Vector3D Vector3DInheritance::cross(const IVector* param) const {
    std::vector<double> comp = param->getComponents();
    double z2 = comp.size() >= 3 ? comp[2] : 0;
    
    double cx = y * z2 - z * comp[1];
    double cy = z * comp[0] - x * z2;
    double cz = x * comp[1] - y * comp[0];
    
    return Vector3D(cx, cy, cz);
}

std::ostream& operator<<(std::ostream& os, const Vector3DInheritance& v) {
    os << "Vector3DInheritance(x=" << std::fixed << std::setprecision(2) << v.x 
       << ", y=" << v.y << ", z=" << v.z << ")";
    return os;
}