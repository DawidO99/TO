#include "CurrencyConverter.h"
#include <stdexcept>

CurrencyConverter::CurrencyConverter(const std::vector<Currency>& currencyList) {
    for (const auto& currency : currencyList) {
        currencies[currency.getCode()] = currency;
    }
}

double CurrencyConverter::convertToPLN(double amount, const std::string& code) {
    if (code == "PLN") return amount;
    return amount * currencies.at(code).getRate();
}

double CurrencyConverter::convertFromPLN(double amount, const std::string& code) {
    if (code == "PLN") return amount;
    return amount / currencies.at(code).getRate();
}

double CurrencyConverter::convert(double amount, const std::string& from, const std::string& to) {
    if (!hasCurrency(from)) {
        throw std::invalid_argument("Unknown source currency: " + from);
    }
    if (!hasCurrency(to)) {
        throw std::invalid_argument("Unknown target currency: " + to);
    }

    // Konwersja przez PLN jako walutę pośrednią
    double amountInPLN = convertToPLN(amount, from);
    return convertFromPLN(amountInPLN, to);
}

bool CurrencyConverter::hasCurrency(const std::string& code) const {
    return currencies.find(code) != currencies.end();
}

std::vector<std::string> CurrencyConverter::getAvailableCurrencies() const {
    std::vector<std::string> codes;
    for (const auto& pair : currencies) {
        codes.push_back(pair.first + " - " + pair.second.getName());
    }
    return codes;
}
