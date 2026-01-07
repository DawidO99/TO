#ifndef CONSOLE_UI_H
#define CONSOLE_UI_H

#include "IUserInterface.h"
#include "ICurrencyConverter.h"
#include "IInputValidator.h"
#include <memory>
#include <string>

class ConsoleUI : public IUserInterface {
private:
    std::shared_ptr<ICurrencyConverter> converter;
    std::shared_ptr<IInputValidator> validator;

    void displayAvailableCurrencies();
    double getValidatedAmount();
    std::string getValidatedCurrency(const std::string& prompt);

public:
    ConsoleUI(std::shared_ptr<ICurrencyConverter> converter, 
              std::shared_ptr<IInputValidator> validator);
    void run() override;
};

#endif // CONSOLE_UI_H
