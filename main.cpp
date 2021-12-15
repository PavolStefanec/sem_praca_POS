//#include <iostream>
//#include "Header_files/App/game.h"
//#include "Header_files/consts.h"
#include <stdio.h>
#include <stdio.h>
#include <iostream>
#include "Header_files/console.h"

using namespace std;

int main(int argc, char* args[]) {
    Console* console = new Console(3);
    console->start(3);
    console->setActivePlayer(1);
    console->drawBoard();
    console->move(6);
    console->move(6);
    console->setActivePlayer(2);
    console->move(6);
    console->setActivePlayer(1);
    console->move(4);
    console->move(28);
    console->move(3);
    delete console;
//    Client *client = new Client();
//    client->connectToServer("31.170.88.172", 9999);
//    delete client;

    return 0;
}