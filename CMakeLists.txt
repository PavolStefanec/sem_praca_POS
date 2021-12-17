cmake_minimum_required(VERSION 3.7.2)
project(Server)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")

add_executable(Server
        main.cpp
        server.cpp
        server.h)

