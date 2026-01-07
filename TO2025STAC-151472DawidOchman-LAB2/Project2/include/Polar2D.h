#ifndef POLAR2D_H
#define POLAR2D_H

#include "IPolar2D.h"
#include "Vector2D.h"
#include <iostream>
#include <iomanip>
#include <cmath>

class Polar2D : public IPolar2D {
protected:
    double r;
    double angle;
    
public:
    Polar2D(double r, double angle);
    
    virtual double getAngle() const override;
    virtual double abs() const override;
    Vector2D toVector2D() const;
    
    friend std::ostream& operator<<(std::ostream& os, const Polar2D& p);
};

#endif
