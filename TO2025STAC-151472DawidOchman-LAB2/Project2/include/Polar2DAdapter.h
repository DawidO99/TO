#ifndef POLAR2DADAPTER_H
#define POLAR2DADAPTER_H

#include "IVector.h"
#include "IPolar2D.h"
#include "Vector2D.h"
#include <iostream>
#include <iomanip>

class Polar2DAdapter : public IVector, public IPolar2D {
private:
    Vector2D* srcVector;
    
public:
    Polar2DAdapter(Vector2D* v);
    
    virtual double abs() const override;
    virtual double getAngle() const override;
    virtual double cdot(const IVector* param) const override;
    virtual std::vector<double> getComponents() const override;
    
    friend std::ostream& operator<<(std::ostream& os, const Polar2DAdapter& p);
};

#endif
