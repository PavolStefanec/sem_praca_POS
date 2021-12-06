//
// Created by palos on 4. 12. 2021.
//

#include "../../Header_files/communication/client.h"

Client::Client() {
}

void Client::initWinSock() {
    ver = MAKEWORD(2, 2);
    int wsResult = WSAStartup(ver, &data);
    if (wsResult != 0) {
        std::cout << "WSA failed to initialize, " << wsResult << std::endl;
        return;
    }
    std::cout << "wsa successfully initialized" << std::endl;
}

void Client::createSocket() {
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        std::cout << "cannot open socket, error " << WSAGetLastError() << std::endl;
        return;
    }
    std::cout << "socket successfully opened" << std::endl;
}

void Client::connectToServer(std::string parIP, int parPort) {
    ipAddress = parIP;
    port = parPort;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

    int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
    if (connResult == SOCKET_ERROR) {
        std::cout << "cant connect to server, error " << WSAGetLastError() << std::endl;
        WSACleanup();
        return;
    }
    char buf[4096];
    std::string userInput;

    do {
        std::cout << ">";
        getline(std::cin, userInput);

        if (userInput.size() > 0) {
            int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
            if (sendResult != SOCKET_ERROR) {
                ZeroMemory(buf, 4096);
                int bytesReceived = recv(sock, buf, 4096, 0);
                if (bytesReceived > 0) {
                    std::cout << "server " << std::string(buf, 0 , bytesReceived) << std::endl;
                }
            }
        }
    } while (userInput.size() > 0);
    closesocket(sock);
}

Client::~Client() {
    WSACleanup();
}

