#ifndef IVECTOR_H
#define IVECTOR_H

#include <vector>

class IVector {
public:
    virtual double abs() const = 0;
    virtual double cdot(const IVector* param) const = 0;
    virtual std::vector<double> getComponents() const = 0;
    virtual ~IVector() {}
};

#endif