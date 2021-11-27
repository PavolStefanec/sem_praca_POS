#include <iostream>
#include <SDL.h>
#include "Header_files/piece.h"

int main(int argc, char* args[]) {
    std::cout << "Hello, World!" << std::endl;

    Piece* piece = new Piece();
    bool a = piece->getIsHome();
    std::cout << a << std::endl;
    return 0;
}
