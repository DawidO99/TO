#ifndef CURRENCY_CONVERTER_H
#define CURRENCY_CONVERTER_H

#include "ICurrencyConverter.h"
#include "Currency.h"
#include <map>
#include <vector>
#include <string>

class CurrencyConverter : public ICurrencyConverter {
private:
    std::map<std::string, Currency> currencies;

    double convertToPLN(double amount, const std::string& code);
    double convertFromPLN(double amount, const std::string& code);

public:
    CurrencyConverter(const std::vector<Currency>& currencyList);
    double convert(double amount, const std::string& from, const std::string& to) override;
    bool hasCurrency(const std::string& code) const override;
    std::vector<std::string> getAvailableCurrencies() const override;
};

#endif // CURRENCY_CONVERTER_H
