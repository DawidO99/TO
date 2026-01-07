#include "InputValidator.h"
#include "ICurrencyConverter.h"
#include <regex>
#include <algorithm>

std::pair<bool, double> InputValidator::validateAmount(const std::string& input) {
    if (input.empty()) {
        return {false, 0.0};
    }

    // Sprawdź czy zawiera tylko cyfry, kropkę lub przecinek
    std::regex amountRegex("^[0-9]+([.,][0-9]+)?$");
    if (!std::regex_match(input, amountRegex)) {
        return {false, 0.0};
    }

    try {
        std::string normalizedInput = input;
        std::replace(normalizedInput.begin(), normalizedInput.end(), ',', '.');
        double amount = std::stod(normalizedInput);
        
        if (amount <= 0) {
            return {false, 0.0};
        }
        
        return {true, amount};
    } catch (...) {
        return {false, 0.0};
    }
}

std::pair<bool, std::string> InputValidator::validateCurrencyCode(
    const std::string& code, 
    const ICurrencyConverter& converter) {
    
    if (code.empty()) {
        return {false, ""};
    }

    std::string upperCode = code;
    std::transform(upperCode.begin(), upperCode.end(), upperCode.begin(), ::toupper);

    if (!converter.hasCurrency(upperCode)) {
        return {false, ""};
    }

    return {true, upperCode};
}
