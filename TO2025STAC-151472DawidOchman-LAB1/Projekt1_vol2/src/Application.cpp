#include "Application.h"
#include "NBPXmlDataProvider.h"
#include "CurrencyConverter.h"
#include "InputValidator.h"
#include "ConsoleUI.h"
#include <iostream>
#include <stdexcept>

Application::Application() {
    dataProvider = std::make_shared<NBPXmlDataProvider>( //make shared zarzadza pamiecia w bezpieczny sposob, jest to smart pointer
        "https://static.nbp.pl/dane/kursy/xml/lasta.xml"
    );
}

void Application::run() {
    try {
        std::cout << "Pobieranie kursów walut z NBP..." << std::endl;
        auto currencies = dataProvider->fetchCurrencies();
        std::cout << "Pobrano " << currencies.size() << " walut." << std::endl;

        auto converter = std::make_shared<CurrencyConverter>(currencies);
        auto validator = std::make_shared<InputValidator>();
        ui = std::make_shared<ConsoleUI>(converter, validator);

        ui->run();
    } catch (const std::exception& e) {
        std::cerr << "Błąd aplikacji: " << e.what() << std::endl;
    }
}
