cmake_minimum_required(VERSION 3.7.2)
project(ludo)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")

add_executable(ludo main.cpp Header_files/App/board.h Source_files/App/board.cpp Header_files/consts.h Header_files/App/field.h Source_files/App/field.cpp Header_files/App/piece.h Source_files/App/piece.cpp Header_files/App/player.h Source_files/App/player.cpp Header_files/App/game.h Source_files/App/game.cpp Header_files/console.h Source_files/console.cpp Header_files/communication/client.h Header_files/communication/server.h Source_files/communication/client.cpp Source_files/communication/server.cpp)


