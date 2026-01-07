cmake_minimum_required(VERSION 3.10)
project(Project2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Project2
        main.cpp
        src/Vector2D.cpp
        src/Vector3D.cpp
        src/Vector3DInheritance.cpp
        src/Polar2D.cpp
        src/Polar2DAdapter.cpp
        src/Polar2DInheritance.cpp
        src/Vector3DDecorator.cpp
)