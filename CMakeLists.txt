cmake_minimum_required(VERSION 3.0)
project(Route_x86)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
        include/Vertex.h
        include/Edge.h
        src/Edge.cpp
        src/Vertex.cpp
        include/MutablePriorityQueue.h
)