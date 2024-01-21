cmake_minimum_required(VERSION 3.25)
project(Lista11)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Lista11
        main.cpp
        ONPCalc.cpp
        ONPCalc.h)
