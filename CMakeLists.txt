cmake_minimum_required(VERSION 3.7.2)
project(Server)

set(CMAKE_CXX_STANDARD 14)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(Server
        main.cpp)

