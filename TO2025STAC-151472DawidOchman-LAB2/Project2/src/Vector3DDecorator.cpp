#include "../include/Vector3DDecorator.h"

Vector3DDecorator::Vector3DDecorator(IVector* v, double z) : srcVector(v), z(z) {}

double Vector3DDecorator::abs() const {
    std::vector<double> comp = srcVector->getComponents();
    double sum = 0;
    for (double c : comp) {
        sum += c * c;
    }
    return sqrt(sum + z * z);
}

double Vector3DDecorator::cdot(const IVector* param) const {
    double result = srcVector->cdot(param);
    std::vector<double> comp = param->getComponents();
    if (comp.size() >= 3) {
        result += z * comp[2];
    }
    return result;
}

std::vector<double> Vector3DDecorator::getComponents() const {
    std::vector<double> comp = srcVector->getComponents();
    return {comp[0], comp[1], z};
}

Vector3D Vector3DDecorator::cross(const IVector* param) const {
    std::vector<double> comp1 = getComponents();
    std::vector<double> comp2 = param->getComponents();
    double z2 = comp2.size() >= 3 ? comp2[2] : 0;
    
    double cx = comp1[1] * z2 - comp1[2] * comp2[1];
    double cy = comp1[2] * comp2[0] - comp1[0] * z2;
    double cz = comp1[0] * comp2[1] - comp1[1] * comp2[0];
    
    return Vector3D(cx, cy, cz);
}

std::ostream& operator<<(std::ostream& os, const Vector3DDecorator& v) {
    std::vector<double> comp = v.srcVector->getComponents();
    os << "Vector3DDecorator(x=" << std::fixed << std::setprecision(2) << comp[0] 
       << ", y=" << comp[1] << ", z=" << v.z << ")";
    return os;
}