#ifndef VECTOR3DINHERITANCE_H
#define VECTOR3DINHERITANCE_H

#include "Vector2D.h"
#include "Vector3D.h"
#include <iostream>
#include <iomanip>

class Vector3DInheritance : public Vector2D {
private:
    double z;
    
public:
    Vector3DInheritance(const Vector2D& v, double z);
    Vector3DInheritance(double x, double y, double z);
    
    virtual std::vector<double> getComponents() const override;
    virtual double abs() const override;
    virtual double cdot(const IVector* param) const override;
    Vector3D cross(const IVector* param) const;
    double getZ() const { return z; }
    
    friend std::ostream& operator<<(std::ostream& os, const Vector3DInheritance& v);
};

#endif
