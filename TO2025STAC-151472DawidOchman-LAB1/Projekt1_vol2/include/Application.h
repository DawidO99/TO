#ifndef APPLICATION_H
#define APPLICATION_H

#include "ICurrencyDataProvider.h"
#include "IUserInterface.h"
#include <memory>

class Application {
private:
    std::shared_ptr<ICurrencyDataProvider> dataProvider;
    std::shared_ptr<IUserInterface> ui;

public:
    Application();
    void run();
};

#endif // APPLICATION_H
