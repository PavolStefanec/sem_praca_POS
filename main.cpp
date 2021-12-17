
#include "Header_files/consts.h"
#include "Header_files/communication/client.h"
#include "Header_files/communication/server.h"
#include <stdio.h>
#include <stdio.h>
//#include <iostream>
//#include "Header_files/console.h"

using namespace std;

int main(int argc, char* args[]) {

    //TEST HRY
//    Console* console = new Console(3);
//    console->start(3);
//    console->setActivePlayer(1);
//    console->drawBoard();
//    console->move(6);
//    console->move(6);
//    console->setActivePlayer(2);
//    console->move(6);
//    console->setActivePlayer(1);
//    console->move(4);
//    console->move(28);
//    console->move(3);
//    delete console;

//TEST KLIENT
//    Client *client = new Client("localhost", 9999);
//    client->connectingToGame();
//    delete client;
//TEST SERVER

    Server* server = new Server(9999,2);
    server->creatingSocket();
    server->binding();
    server->connectPlayerToGame();
    printf("START game!\n");
    //ide Pajova cast komunikacie a vlakien...
    server->closeSocket();
    delete server;
    return 0;
}