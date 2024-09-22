cmake_minimum_required(VERSION 3.28)
set (PROJECT_NAME "Segment tree generalized implementation")
project(${PROJECT_NAME}
        VERSION 0.1
        DESCRIPTION "Generalized Segment tree, using C++20"
        LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(./include)
add_subdirectory(./tests)
