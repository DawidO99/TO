#ifndef VECTOR3DDECORATOR_H
#define VECTOR3DDECORATOR_H

#include "IVector.h"
#include "Vector3D.h"
#include <iostream>
#include <iomanip>
#include <cmath>

class Vector3DDecorator : public IVector {
private:
    IVector* srcVector;
    double z;

public:
    Vector3DDecorator(IVector* v, double z);

    virtual double abs() const override;
    virtual double cdot(const IVector* param) const override;
    virtual std::vector<double> getComponents() const override;
    Vector3D cross(const IVector* param) const;
    double getZ() const { return z; }

    friend std::ostream& operator<<(std::ostream& os, const Vector3DDecorator& v);
};

#endif