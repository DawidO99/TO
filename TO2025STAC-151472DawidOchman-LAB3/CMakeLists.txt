cmake_minimum_required(VERSION 3.16)

project(SimulationLab3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_standard_project_setup()

add_executable(SimulationLab3
        main.cpp
        MainWindow.cpp
        MainWindow.h
        SimulationCore.cpp
        SimulationCore.h
        Vector2D.h
)

target_link_libraries(SimulationLab3 PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)

# Wymagane dla MOC (Meta-Object Compiler) Qt
set_target_properties(SimulationLab3 PROPERTIES
        WIN32_EXECUTABLE ON
        MACOSX_BUNDLE ON
)