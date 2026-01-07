#ifndef VECTOR3D_H
#define VECTOR3D_H

#include "IVector.h"
#include <iostream>
#include <iomanip>
#include <cmath>

class Vector3D : public IVector {
protected:
    double x;
    double y;
    double z;
    
public:
    Vector3D(double x, double y, double z);
    
    virtual std::vector<double> getComponents() const override;
    virtual double abs() const override;
    virtual double cdot(const IVector* param) const override;
    Vector3D cross(const IVector* param) const;
    
    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }
    
    friend std::ostream& operator<<(std::ostream& os, const Vector3D& v);
};

#endif