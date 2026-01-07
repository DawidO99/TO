#include "ConsoleUI.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>#


ConsoleUI::ConsoleUI(std::shared_ptr<ICurrencyConverter> converter, 
                     std::shared_ptr<IInputValidator> validator)
    : converter(converter), validator(validator) {}

void ConsoleUI::displayAvailableCurrencies() {
    std::cout << "\n=== Dostępne waluty ===" << std::endl;
    auto currencies = converter->getAvailableCurrencies();
    for (const auto& currency : currencies) {
        std::cout << "  " << currency << std::endl;
    }
    std::cout << std::endl;
}

double ConsoleUI::getValidatedAmount() {
    std::string input;
    while (true) {
        std::cout << "Podaj kwotę do przeliczenia: ";
        std::getline(std::cin, input);

        auto [valid, amount] = validator->validateAmount(input);
        if (valid) {
            return amount;
        }
        std::cout << "Błąd! Podaj poprawną kwotę (liczba większa od 0)." << std::endl;
    }
}

std::string ConsoleUI::getValidatedCurrency(const std::string& prompt) {
    std::string input;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);

        auto [valid, code] = validator->validateCurrencyCode(input, *converter);
        if (valid) {
            return code;
        }
        std::cout << "Błąd! Podaj poprawny kod waluty (np. USD, EUR, PLN)." << std::endl;
    }
}

void ConsoleUI::run() {
    std::cout << "\n╔════════════════════════════════════════╗" << std::endl;
    std::cout << "║  KONWERTER WALUT NBP                  ║" << std::endl;
    std::cout << "╚════════════════════════════════════════╝" << std::endl;

    displayAvailableCurrencies();

    double amount = getValidatedAmount();
    std::string fromCurrency = getValidatedCurrency("Podaj kod waluty źródłowej: ");
    std::string toCurrency = getValidatedCurrency("Podaj kod waluty docelowej: ");

    try {
        double result = converter->convert(amount, fromCurrency, toCurrency);
        
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "\n╔════════════════════════════════════════╗" << std::endl;
        std::cout << "║  WYNIK KONWERSJI                      ║" << std::endl;
        std::cout << "╚════════════════════════════════════════╝" << std::endl;
        std::cout << "  " << amount << " " << fromCurrency 
                  << " = " << result << " " << toCurrency << std::endl;
        std::cout << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Błąd podczas konwersji: " << e.what() << std::endl;
    }
}
