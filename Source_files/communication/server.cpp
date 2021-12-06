//
// Created by palos on 2. 12. 2021.
//

#include "../../Header_files/communication/server.h"

Server::Server() {
    // initialize WinSock
    ver = MAKEWORD(2, 2);
    int wsOK = WSAStartup(ver, &wsData);
    if (wsOK != 0) {
        std::cout << "WSA failed to initialize" << std::endl;
        return;
    }
    std::cout << "WSA successfully initialized" << std::endl;


    // create socket
    listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == INVALID_SOCKET) {
        std::cout << "cannot open socket, error " << WSAGetLastError() << std::endl;
        return;
    }
    std::cout << "socket successfully opened" << std::endl;
}

void Server::bindSocket(int parPort) {
    port = parPort;
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    hint.sin_addr.S_un.S_addr = INADDR_ANY;

    int bindResult = bind(listening, (sockaddr*)&hint, sizeof(hint));
    if (bindResult != 0) {
        std::cout << "port binding failed" << std::endl;
        return;
    }
    std::cout << "port binding succeeded" << std::endl;
}

void Server::startListening() {
    int lResult = listen(listening, SOMAXCONN);
    if (lResult != 0) {
        std::cout << "failed to start listening on port " << port << std::endl;
        return;
    }
    std::cout << "started listening on port " << port << std::endl;

    sockaddr_in client;
    int clientSize = sizeof(client);

    SOCKET clientSocket = accept(listening, (sockaddr*)& client, &clientSize);
    if (clientSocket == INVALID_SOCKET) {
        std::cout << "client socket is invalid" << std::endl;
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
            std::cout << "error in function recv() " << std::endl;

            break;
        }

        if (bytesReceived == 0) {
            std::cout << "client disconnected" << std::endl;
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