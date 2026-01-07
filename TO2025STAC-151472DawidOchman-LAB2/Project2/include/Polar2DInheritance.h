#ifndef POLAR2DINHERITANCE_H
#define POLAR2DINHERITANCE_H

#include "Polar2D.h"

class Polar2DInheritance : public Polar2D {
public:
    Polar2DInheritance(double r, double angle);
    Vector2D toVector2D() const;
};

#endif