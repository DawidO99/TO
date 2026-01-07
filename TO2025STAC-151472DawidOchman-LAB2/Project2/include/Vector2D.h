#ifndef VECTOR2D_H
#define VECTOR2D_H

#include "IVector.h"
#include "Vector3D.h"
#include <iostream>
#include <iomanip>
#include <cmath>

class Vector2D : public IVector {
protected:
    double x;
    double y;
    
public:
    Vector2D(double x, double y);
    
    virtual std::vector<double> getComponents() const override;
    virtual double abs() const override;
    virtual double cdot(const IVector* param) const override;
    Vector3D cross(const IVector* param) const;
    double getAngle() const;
    
    double getX() const { return x; }
    double getY() const { return y; }
    
    friend std::ostream& operator<<(std::ostream& os, const Vector2D& v);
};

#endif
