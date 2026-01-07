#ifndef INPUT_VALIDATOR_H
#define INPUT_VALIDATOR_H

#include "IInputValidator.h"

class InputValidator : public IInputValidator {
public:
    std::pair<bool, double> validateAmount(const std::string& input) override;
    std::pair<bool, std::string> validateCurrencyCode(
        const std::string& code, 
        const ICurrencyConverter& converter) override;
};

#endif // INPUT_VALIDATOR_H
