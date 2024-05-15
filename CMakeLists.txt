cmake_minimum_required(VERSION 3.10)
project(Route_x86)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include
        data)

add_executable(Route_x86
        main.cpp
        include/GraphLoader.h
        src/GraphLoader.cpp
        include/GraphController.h
        src/GraphController.cpp
        include/UserInterface.h
        src/UserInterface.cpp
)