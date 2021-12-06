#include <iostream>
#include <SDL.h>

#include "Header_files/communication/server.h"
#include "Header_files/communication/client.h"


int main(int argc, char* args[]) {
    std::cout << "Hello, World!" << std::endl;

    Server* server = new Server();
    Client* client = new Client();

//    server->initWinSock();
//    server->createSocket();
//    server->bindSocket(9999);
//    server->startListening();


    client->initWinSock();
    client->createSocket();
    client->connectToServer("127.0.0.1", 9999);


    delete client;
    delete server;

    return 0;
}
