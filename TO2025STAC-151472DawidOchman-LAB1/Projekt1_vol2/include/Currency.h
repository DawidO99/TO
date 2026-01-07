#ifndef CURRENCY_H
#define CURRENCY_H

#include <string>

class Currency {
private:
    std::string code;
    std::string name;
    double rate;

public:
    Currency();
    Currency(const std::string& code, const std::string& name, double rate);

    std::string getCode() const;
    std::string getName() const;
    double getRate() const;
};

#endif // CURRENCY_H
