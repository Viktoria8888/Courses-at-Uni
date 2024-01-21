cmake_minimum_required(VERSION 3.25)
project(Lista11_2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Lista11_2
        Expression.cpp
        Function.cpp
        Function.hpp
        main.cpp
        Operand.cpp
        Operand.hpp
        Symbol.cpp
        Symbol.hpp Queue.h)
