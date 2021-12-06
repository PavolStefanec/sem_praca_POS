cmake_minimum_required(VERSION 3.20)
project(ludo)

set(CMAKE_CXX_STANDARD 14)
set(SDL2_INCLUDE_DIR C:/libs/SDL/include)
set(SDL2_LIB_DIR C:/libs/SDL/lib/x86)
include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

add_executable(ludo main.cpp Header_files/board.h Source_files/board.cpp Header_files/consts.h Header_files/field.h Source_files/field.cpp Header_files/piece.h Source_files/piece.cpp Header_files/player.h Source_files/player.cpp Header_files/communication/server.h Source_files/communication/server.cpp Source_files/communication/client.cpp Header_files/communication/client.h)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2)