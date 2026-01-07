#include "Application.h"
#include <curl/curl.h>

int main() {
    curl_global_init(CURL_GLOBAL_DEFAULT); //biblioteka curl, potrzebna do xml'a

    Application app;
    app.run();

    curl_global_cleanup();
    return 0;
}
