cmake_minimum_required(VERSION 3.25)
project(Lista7_2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Lista7_2
        AI.cpp
        GameState.cpp
        GameState.h
        TicTacToeGame.cpp
        TicTacToeGame.h)
