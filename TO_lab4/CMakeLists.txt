cmake_minimum_required(VERSION 3.16)

# Nazwa projektu
project(SKKM_Symulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Włącz automatyczne generowanie MOC (dla Qt)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Znajdź biblioteki Qt
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# --- KLUCZOWA ZMIANA: Wskazanie folderu z nagłówkami ---
# Dzięki temu w kodzie piszesz #include "Car.h" zamiast #include "../include/Car.h"
include_directories(include)

# Definicja plików źródłowych i nagłówkowych (dla widoczności w IDE)
set(SOURCE_FILES
        # Pliki źródłowe
        src/main.cpp
        src/Car.cpp
        src/SKKM.cpp
        src/MapWidget.cpp
        src/Unit.cpp

        # Pliki nagłówkowe (warto dodać, żeby widzieć je w drzewie projektu CLion)
        include/Car.h
        include/Location.h
        include/MapWidget.h
        include/SKKM.h
        include/Strategies.h
        include/Unit.h
        include/Unit.h
        src/Unit.cpp
        include/Location.h
        include/Strategies.h
        include/Car.h
        src/Car.cpp
        include/SKKM.h
        src/SKKM.cpp
        include/MapWidget.h
        src/MapWidget.cpp
)

add_executable(SKKM_Symulator ${SOURCE_FILES})

target_link_libraries(SKKM_Symulator PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)