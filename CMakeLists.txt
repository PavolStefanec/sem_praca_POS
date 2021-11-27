cmake_minimum_required(VERSION 3.20)
project(ludo)

set(CMAKE_CXX_STANDARD 14)
set(SDL2_INCLUDE_DIR C:/libs/SDL/include)
set(SDL2_LIB_DIR C:/libs/SDL/lib/x86)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})
add_executable(ludo main.cpp Header_files/piece.h Source_files/piece.cpp)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2)