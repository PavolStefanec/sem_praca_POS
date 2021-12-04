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
    std::string ipAddress = ""; // server IP address
    int port = 0;   // listening port on the server
    WSAData data;
    WORD ver;
    SOCKET sock;
    sockaddr_in hint;

public:
    Client();
    void initWinSock();
    void createSocket();
    void connectToServer();
    ~Client();
};


