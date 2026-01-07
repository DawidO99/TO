cmake_minimum_required(VERSION 3.10)
project(Projekt1_vol2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Znajdź bibliotekę CURL
find_package(CURL REQUIRED)

# Dodaj ścieżkę do plików nagłówkowych
include_directories(include)

# Lista wszystkich plików źródłowych
set(SOURCES
    src/Currency.cpp
    src/HttpClient.cpp
    src/NBPXmlDataProvider.cpp
    src/CurrencyConverter.cpp
    src/InputValidator.cpp
    src/ConsoleUI.cpp
    src/Application.cpp
    main.cpp
)

# Lista wszystkich plików nagłówkowych
set(HEADERS
    include/Currency.h
    include/ICurrencyDataProvider.h
    include/NBPXmlDataProvider.h
    include/ICurrencyConverter.h
    include/CurrencyConverter.h
    include/IInputValidator.h
    include/InputValidator.h
    include/IUserInterface.h
    include/ConsoleUI.h
    include/HttpClient.h
    include/Application.h
)

# Dodaj plik wykonywalny
add_executable(Projekt1_vol2 ${SOURCES} ${HEADERS})

# Linkuj z biblioteką CURL
target_link_libraries(Projekt1_vol2 CURL::libcurl)

# Opcje kompilacji
if(MSVC)
    target_compile_options(Projekt1_vol2 PRIVATE /W4)
else()
    target_compile_options(Projekt1_vol2 PRIVATE -Wall -Wextra -pedantic)
endif()
