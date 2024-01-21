cmake_minimum_required(VERSION 3.25)
project(Lista6)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Lista6
        Expression.cpp
        Expression.h main.cpp)
