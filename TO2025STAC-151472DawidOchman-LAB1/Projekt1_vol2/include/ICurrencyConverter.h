#ifndef ICURRENCY_CONVERTER_H
#define ICURRENCY_CONVERTER_H

#include <string>
#include <vector>

class ICurrencyConverter {
public:
    virtual ~ICurrencyConverter() = default;
    virtual double convert(double amount, const std::string& from, const std::string& to) = 0;
    virtual bool hasCurrency(const std::string& code) const = 0;
    virtual std::vector<std::string> getAvailableCurrencies() const = 0;
};

#endif // ICURRENCY_CONVERTER_H
