#ifndef IINPUT_VALIDATOR_H
#define IINPUT_VALIDATOR_H

#include <string>
#include <utility>

class ICurrencyConverter;

class IInputValidator {
public:
    virtual ~IInputValidator() = default;
    virtual std::pair<bool, double> validateAmount(const std::string& input) = 0;
    virtual std::pair<bool, std::string> validateCurrencyCode(
        const std::string& code, 
        const ICurrencyConverter& converter) = 0;
};

#endif // IINPUT_VALIDATOR_H
