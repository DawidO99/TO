#ifndef NBP_XML_DATA_PROVIDER_H
#define NBP_XML_DATA_PROVIDER_H

#include "ICurrencyDataProvider.h"
#include "HttpClient.h"
#include <string>
#include <vector>

class NBPXmlDataProvider : public ICurrencyDataProvider {
private:
    std::string url;
    HttpClient httpClient;

    std::string extractValue(const std::string& xml, const std::string& tag, size_t& pos);
    std::vector<Currency> parseXml(const std::string& xmlContent);

public:
    NBPXmlDataProvider(const std::string& url);
    std::vector<Currency> fetchCurrencies() override;
};

#endif // NBP_XML_DATA_PROVIDER_H
