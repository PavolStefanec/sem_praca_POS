cmake_minimum_required(VERSION 3.20)
project(untitled)

set(CMAKE_CXX_STANDARD 14)
set(SDL2_INCLUDE_DIR C:/libs/SDL/include)
set(SDL2_LIB_DIR C:/libs/SDL/lib/x86)
include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})



add_executable(untitled main.cpp Header_files/App/board.h Source_files/App/board.cpp Header_files/consts.h Header_files/App/field.h Source_files/App/field.cpp Header_files/App/piece.h Source_files/App/piece.cpp Header_files/App/player.h Source_files/App/player.cpp Header_files/GUI/graphicsSystem.h Source_files/GUI/graphicsSystem.cpp Header_files/App/game.h Source_files/App/game.cpp Header_files/GUI/GUIboard.h Source_files/GUI/GUIboard.cpp Header_files/GUI/GUIfield.h Source_files/GUI/GUIfield.cpp Header_files/GUI/GUIpiece.h Source_files/GUI/GUIpiece.cpp Header_files/input.file.h Source_files/input.file.cpp Header_files/GUI/GUIgame.h Source_files/GUI/GUIgame.cpp)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2 SDL2_IMAGE)


