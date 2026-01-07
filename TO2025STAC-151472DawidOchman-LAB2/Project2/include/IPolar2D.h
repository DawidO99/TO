#ifndef PROJECT2_IPOLAR2D_H
#define PROJECT2_IPOLAR2D_H

class IPolar2D
{
    public:
        virtual ~IPolar2D() = default;
        virtual double getAngle() const = 0;
        virtual double abs() const = 0;
};
#endif