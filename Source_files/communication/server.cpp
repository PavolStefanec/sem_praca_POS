#include "../../Header_files//communication/server.h"

Server::Server(int port, int pNumberOfPlayer) {
    open = true;
    numberOfPlayers = pNumberOfPlayer;
    lastPlayerId = 0;

    bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);
}

void Server::creatingSocket() {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        open = false;
        return;
    }
}

void Server::binding() {
    if (open) {
        if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
            perror("Error binding socket address");
            open = false;
            return;
        }
    }
}

void Server::listening() {
    listen(sockfd, 5);
    cli_len = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &cli_len);
    if (newsockfd < 0) {
        perror("ERROR on accept");
        open = false;
        return;
    }
}

void Server::connectPlayerToGame() {
    while (lastPlayerId != numberOfPlayers) {
        listening();
        if (open) {
            bzero(buffer, 256);
            n = read(newsockfd, buffer, 255);
            if (n < 0) {
                perror("Error reading from socket");
                open = false;
                return;
            }
            int message = atoi(buffer);
            if (message == 0) {
                const char* number = std::to_string(numberOfPlayers).c_str();
                n = write(newsockfd, number, strlen(number)+1);
                if (n < 0)
                {
                    perror("Error writing to socket");
                    open = false;
                    return;
                }

                lastPlayerId++;
                const char* idPlayer = std::to_string(lastPlayerId).c_str();
                n = write(newsockfd, idPlayer, strlen(idPlayer)+1);
                if (n < 0)
                {
                    perror("Error writing to socket");
                    open = false;
                    return;
                }
                printf("Do hry sa pripojil hrac s id: %d", lastPlayerId);
            }
        }
    }
    printf("Vsetci hraci su pripojeny!\nLUDO sa zacina!\n");
}

void Server::closeSocket() {
    close(newsockfd);
    close(sockfd);
}

Server::~Server() {
}