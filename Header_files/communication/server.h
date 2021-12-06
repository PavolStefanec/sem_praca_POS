#pragma once
//
// Created by palos on 2. 12. 2021.
//

#include <iostream>
#include <WS2tcpip.h>
#include <string>

#pragma comment (lib, "Ws2_32.lib")

class Server {
private:
    WSADATA wsData;
    WORD ver;
    SOCKET listening;
    int port;


public:
    Server();
    void initWinSock();
    void createSocket();
    void bindSocket(int parPort);
    void startListening();
    void closeSocket(SOCKET parSocket);
    ~Server();
};

