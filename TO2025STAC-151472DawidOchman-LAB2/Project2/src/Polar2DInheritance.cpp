#include "../include/Polar2DInheritance.h"

Polar2DInheritance::Polar2DInheritance(double r, double angle) : Polar2D(r, angle) {}

Vector2D Polar2DInheritance::toVector2D() const {
    return Polar2D::toVector2D();
}