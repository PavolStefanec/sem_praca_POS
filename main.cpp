#include <iostream>
#include "server.h"
int main() {
    Server* server = new Server(9999, 1);
    server->creatingSocket();
    server->binding();
    server->connectPlayerToGame();
    server->closeSocket();
    delete server;
    return 0;
}