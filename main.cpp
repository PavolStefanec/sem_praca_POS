#include <iostream>
#include <SDL.h>
#include "Header_files/piece.h"
int main(int argc, char* args[]) {
    std::cout << "Hello, World!" << std::endl;
    Piece piece;
    std::cout << piece.getIsHome() <<std::endl;
    return 0;
}
