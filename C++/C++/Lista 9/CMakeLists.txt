cmake_minimum_required(VERSION 3.25)
project(Lista_9)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Lista_9
        main1.cpp
        MyList.cpp
        MyList.h MyStack.h Queue.h)
