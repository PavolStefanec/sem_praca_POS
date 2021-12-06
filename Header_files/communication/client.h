#pragma once

//
// Created by palos on 4. 12. 2021.
//

#include <iostream>
#include <WS2tcpip.h>
#include <string>

#pragma comment(lib, "ws2_32.lib")

class Client {
private:
    std::string ipAddress;
    int port;
    WSAData data;
    WORD ver;
    SOCKET sock;
    sockaddr_in hint;

public:
    Client();
    void initWinSock();
    void createSocket();
    void connectToServer(std::string parIP, int parPort);
    ~Client();
};


