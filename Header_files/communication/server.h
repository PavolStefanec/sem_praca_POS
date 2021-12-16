#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <iostream>

using namespace std;

class Server {
private:
    int sockfd, newsockfd;
    socklen_t cli_len;
    //server
    struct sockaddr_in serv_addr;
    //klienti
    struct sockaddr_in cli_addr;
    int n;
    char buffer[256];
    bool open;

    int numberOfPlayers;
    int lastPlayerId;
    //vlakna
public:
    Server(int port, int pNumberOfPlayers);
    ~Server();
    void creatingSocket();
    void binding();
    void listening();
    void connectPlayerToGame();
    void startGame();
    void communication();
    void closeSocket();
    int getNumberOfPlayer();
};