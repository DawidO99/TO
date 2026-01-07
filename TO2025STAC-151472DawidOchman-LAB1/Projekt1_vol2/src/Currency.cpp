#include "Currency.h"

Currency::Currency() : code(""), name(""), rate(0.0) {}

Currency::Currency(const std::string& code, const std::string& name, double rate)
    : code(code), name(name), rate(rate) {}

std::string Currency::getCode() const {
    return code;
}

std::string Currency::getName() const {
    return name;
}

double Currency::getRate() const {
    return rate;
}
