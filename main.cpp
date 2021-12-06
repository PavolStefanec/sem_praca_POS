#include <iostream>
#include <SDL.h>

#include "Header_files/communication/client.h"
#include "Header_files/communication/server.h"


int main(int argc, char* args[]) {

//    std::string input;
//    std::cout << "1 pre spustenie servera, ine pre clienta" << std::endl;
//    std::cin >> input;

//    if (input == "1") {
//        Server *server = new Server();
//        server->bindSocket(9999);
//        server->startListening();
//        delete server;
//    } else {
        Client *client = new Client();
        client->connectToServer("127.0.0.1", 9999);
        delete client;
//    }

    return 0;
}