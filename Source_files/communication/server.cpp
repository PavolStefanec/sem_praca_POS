//
// Created by palos on 2. 12. 2021.
//

#include "../../Header_files/communication/server.h"

Server::Server() {

}

void Server::initWinSock() {
    ver = MAKEWORD(2, 2);

    int wsOK = WSAStartup(ver, &wsData);
    if (wsOK != 0) {
        std::cerr << "Error" << std::endl;
        return;
    }
}

void Server::createSocket() {
    listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == INVALID_SOCKET) {
        std::cerr << "Can not create socket" << std::endl;
        return;
    }
}

void Server::bindSocket() {
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    hint.sin_addr.S_un.S_addr = INADDR_ANY;

    bind(listening, (sockaddr*)&hint, sizeof(hint));
}

void Server::startListening() {
    listen(listening, SOMAXCONN);


    sockaddr_in client;
    int clientSize = sizeof(client);

    SOCKET clientSocket = accept(listening, (sockaddr*)& client, &clientSize);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Error" << std::endl;
        return;
    }

    char host[NI_MAXHOST];   // client's remote name
    char service[NI_MAXHOST]; // service (port) the client is connected on

    ZeroMemory(host, NI_MAXHOST);
    ZeroMemory(service, NI_MAXHOST);

    if (getnameinfo((sockaddr*)& client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0) {
        std::cout << host << " connected on port " << service << std::endl;
    } else {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        std::cout << host << " connected on port " << ntohs(client.sin_port) << std::endl;
    }

    closeSocket(listening);

    char buf[40496];

    while (true) {
        ZeroMemory(buf, 4096);

        int bytesReceived = recv(clientSocket, buf, 4096, 0);
        if (bytesReceived == SOCKET_ERROR) {
            std::cerr << "error in recv() " << std::endl;

            break;
        }

        if (bytesReceived == 0) {
            std::cout << "client disconneted" << std::endl;
            break;
        }

        std::cout << std::string(buf, 0, bytesReceived);

        send(clientSocket, buf, bytesReceived + 1, 0);
    }

    closeSocket(clientSocket);
}

void Server::closeSocket(SOCKET parSocket) {
    closesocket(parSocket);
}

Server::~Server() {
    WSACleanup();
}