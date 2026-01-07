#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <cmath>

class Vector2D {
private:
    double x;
    double y;

public:
    Vector2D(double x = 0.0, double y = 0.0) : x(x), y(y) {}

    double getX() const { return x; }
    double getY() const { return y; }

    void setX(double newX) { x = newX; }
    void setY(double newY) { y = newY; }

    // Długość wektora
    double abs() const {
        return std::sqrt(x * x + y * y);
    }

    // Normalizacja
    Vector2D normalize() const {
        double length = abs();
        if (length > 0.0001) {
            return Vector2D(x / length, y / length);
        }
        return Vector2D(0, 0);
    }

    // Odległość do innego wektora
    double distanceTo(const Vector2D& other) const {
        double dx = x - other.x;
        double dy = y - other.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    // Operatory
    Vector2D operator+(const Vector2D& v) const {
        return Vector2D(x + v.x, y + v.y);
    }

    Vector2D operator-(const Vector2D& v) const {
        return Vector2D(x - v.x, y - v.y);
    }

    Vector2D operator*(double scalar) const {
        return Vector2D(x * scalar, y * scalar);
    }

    Vector2D operator/(double scalar) const {
        return Vector2D(x / scalar, y / scalar);
    }

    Vector2D& operator+=(const Vector2D& v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    Vector2D& operator*=(double scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    // Iloczyn skalarny
    double dot(const Vector2D& v) const {
        return x * v.x + y * v.y;
    }

    // Rotacja o kąt (w radianach)
    Vector2D rotate(double angle) const {
        double cos_a = std::cos(angle);
        double sin_a = std::sin(angle);
        return Vector2D(
            x * cos_a - y * sin_a,
            x * sin_a + y * cos_a
        );
    }

    // Kąt wektora
    double angle() const {
        return std::atan2(y, x);
    }
};

#endif // VECTOR2D_H