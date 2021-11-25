cmake_minimum_required(VERSION 3.20)
project(untitled)

set(CMAKE_CXX_STANDARD 14)
set(SDL2_INCLUDE_DIR C:/Users/miska/Documents/Data/ProgramovacieJazyky/C/C++/PrincipyOperacnychSystemov/SemestralnaPraca2021/sem_praca_POS/SDL/include)
set(SDL2_LIB_DIR C:/Users/miska/Documents/Data/ProgramovacieJazyky/C/C++/PrincipyOperacnychSystemov/SemestralnaPraca2021/sem_praca_POS/SDL/lib/x86)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

add_executable(untitled main.cpp)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2)