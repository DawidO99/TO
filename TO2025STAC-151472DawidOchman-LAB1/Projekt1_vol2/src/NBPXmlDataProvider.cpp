#include "NBPXmlDataProvider.h"
#include <algorithm>
#include <stdexcept>

NBPXmlDataProvider::NBPXmlDataProvider(const std::string& url) : url(url) {}

std::string NBPXmlDataProvider::extractValue(const std::string& xml, const std::string& tag, size_t& pos) {
    std::string openTag = "<" + tag + ">";
    std::string closeTag = "</" + tag + ">";
    
    size_t start = xml.find(openTag, pos);
    if (start == std::string::npos) return "";
    
    start += openTag.length();
    size_t end = xml.find(closeTag, start);
    if (end == std::string::npos) return "";
    
    pos = end + closeTag.length();
    return xml.substr(start, end - start);
}

std::vector<Currency> NBPXmlDataProvider::parseXml(const std::string& xmlContent) {
    std::vector<Currency> currencies;
    
    // Dodaj PLN jako walutę bazową
    currencies.push_back(Currency("PLN", "Polski złoty", 1.0));
    
    size_t pos = 0;
    while (true) {
        size_t positionStart = xmlContent.find("<pozycja>", pos);
        if (positionStart == std::string::npos) break;
        
        size_t positionEnd = xmlContent.find("</pozycja>", positionStart);
        if (positionEnd == std::string::npos) break;
        
        std::string positionXml = xmlContent.substr(
            positionStart, 
            positionEnd - positionStart + 11
        );
        
        size_t innerPos = 0;
        std::string code = extractValue(positionXml, "kod_waluty", innerPos);
        innerPos = 0;
        std::string name = extractValue(positionXml, "nazwa_waluty", innerPos);
        innerPos = 0;
        std::string rateStr = extractValue(positionXml, "kurs_sredni", innerPos);
        
        if (!code.empty() && !rateStr.empty()) {
            // Zamień przecinek na kropkę
            std::replace(rateStr.begin(), rateStr.end(), ',', '.');
            double rate = std::stod(rateStr);
            currencies.push_back(Currency(code, name, rate));
        }
        
        pos = positionEnd + 11;
    }
    
    return currencies;
}

std::vector<Currency> NBPXmlDataProvider::fetchCurrencies() {
    try {
        std::string xmlContent = httpClient.get(url); //pobieramy xml z neta
        return parseXml(xmlContent);
    } catch (const std::exception& e) {
        throw std::runtime_error("Error fetching currency data: " + std::string(e.what()));
    }
}
