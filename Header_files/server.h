#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include <iostream>

using namespace std;

typedef struct data {
    int jeNaTahu;
    int posuvaSaPanak;
    int poslednyHod;
    bool jeVyherca;
    int tahID;

    pthread_mutex_t* mutex;
    pthread_cond_t* jeHodene;
    pthread_cond_t* jeOdohrane;
} DATA;

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
    static DATA data;
    //vlakna
public:
    Server(int port);
    ~Server();
    void creatingSocket();
    void binding();
    void listening();
    void communication();
    void hra();
    void closeSocket();
    static void hodKockou();
    static void* tah(int parHrac);
    static void* update(int parHrac);
};