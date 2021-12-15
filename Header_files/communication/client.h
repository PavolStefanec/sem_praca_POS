#pragma once

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../console.h"

using namespace std;

class Client {
private:
    int sockfd;
    int n;
    struct sockaddr_in serv_addr;
    struct hostent* server;
    char buffer[256];
    Console* console;

public:
    Client(char* ipAddress, int parPort);
    void connectToServer();
};


