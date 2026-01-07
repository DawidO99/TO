#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <string>

class HttpClient {
private:
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);

public:
    std::string get(const std::string& url);
};

#endif // HTTP_CLIENT_H
