cmake_minimum_required(VERSION 3.7.2)
project(ludo)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

#add_executable(ludo main.cpp Header_files/App/board.h Source_files/App/board.cpp Header_files/consts.h Header_files/App/field.h Source_files/App/field.cpp Header_files/App/piece.h Source_files/App/piece.cpp Header_files/App/player.h Source_files/App/player.cpp Header_files/App/game.h Source_files/App/game.cpp Header_files/console.h Source_files/console.cpp Header_files/client.h Source_files/client.cpp)
add_executable(ludo main.cpp Header_files/consts.h Header_files/console.h Header_files/App/board.h Header_files/App/field.h Header_files/App/game.h Header_files/App/piece.h Source_files/console.cpp Source_files/App/board.cpp Source_files/App/field.cpp Source_files/App/game.cpp Source_files/App/piece.cpp)
