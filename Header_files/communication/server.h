#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#pragma comment (lib, "Ws2_32.lib")
typedef struct data {
    int kocka;

    pthread_mutex_t  * mutex;
    pthread_cond_t * hodeneKockou;
} DATA;

class Server {
private:
    int sockfd, newsockfd;
    socklen_t cli_len;
    struct sockaddr_in serv_addr;
    struct sockaddr_in cli_addr;
    int n;
    char buffer[256];

public:
    Server(int parPort);
    void bindSocket();
    void startListening();
};

