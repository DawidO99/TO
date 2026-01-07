#ifndef ICURRENCY_DATA_PROVIDER_H
#define ICURRENCY_DATA_PROVIDER_H

#include <vector>
#include "Currency.h"

class ICurrencyDataProvider {
public:
    virtual ~ICurrencyDataProvider() = default;
    virtual std::vector<Currency> fetchCurrencies() = 0;
};

#endif // ICURRENCY_DATA_PROVIDER_H
