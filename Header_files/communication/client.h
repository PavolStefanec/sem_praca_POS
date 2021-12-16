#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include "../console.h"

class Client {
private:
    int sockfd;
    int n;
    struct sockaddr_in serv_addr;
    struct hostent* server;
    bool open;
    char buffer[256];

    int idPlayer;
    int numberOfPlayers;
    Console* game;

public:
    Client(char* name, int port);
    void creatingSocket();
    void connecting();
    void connectingToGame();
    void startGame();
    void closeSocket();
    ~Client();
};
