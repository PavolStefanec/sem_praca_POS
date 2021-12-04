#include <iostream>
#include "Header_files/GUI/graphicsSystem.h"
#include "Header_files/App/piece.h"
#include "Header_files/App/game.h"
#include "Header_files/consts.h"

int main(int argc, char* args[]) {
    std::cout << "Hello, World!" << std::endl;
    GraphicsSystem* graphicsSystem = new GraphicsSystem();
    graphicsSystem->loadImage();
    graphicsSystem->clearWindow();
    graphicsSystem->drawImage();
    SDL_Delay(5000);
    //Game* game = new Game(3);
    //delete game;
    delete graphicsSystem;
    return 0;
}