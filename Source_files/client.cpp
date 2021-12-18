#include "../Header_files/client.h"

Client::Client(char* name, int port) {
    open = true;
    idPlayer = 0;
    numberOfPlayers = 0;
    server = gethostbyname(name);
    if (server == NULL)
    {
        fprintf(stderr, "Error, no such host\n");
        open = false;
        return;
    }

    bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy(
            (char*)server->h_addr,
            (char*)&serv_addr.sin_addr.s_addr,
            server->h_length
    );
    serv_addr.sin_port = htons(port);
}

void Client::creatingSocket() {
    if (open) {
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
            perror("Error creating socket");
            open = false;
            return;
        }
    }
}

void Client::connecting() {
    if (open) {
        if(connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
        {
            perror("Error connecting to socket");
            open = false;
            return;
        }
    }
}

void Client::connectingToGame() {
    creatingSocket();
    connecting();
    if (open) {
        printf("Pripajanie do hry...\n");
        const char* idPlayerCh = std::to_string(idPlayer).c_str();
        n = write(sockfd, idPlayerCh, strlen(idPlayerCh));
        if (n < 0)
        {
            perror("Error writing to socket");
            open = false;
            return;
        }

        bzero(buffer,256);
        n = read(sockfd, buffer, 255);
        if (n < 0)
        {
            perror("Error reading from socket");
            open = false;
            return;
        }
        numberOfPlayers = atoi(buffer);
        printf("Celkovy pocet hracov v hre: %d\n", numberOfPlayers);

        bzero(buffer,256);
        n = read(sockfd, buffer, 255);
        if (n < 0)
        {
            perror("Error reading from socket");
            open = false;
            return;
        }
        idPlayer = atoi(buffer);
        printf("Si v hre!\n");
        printf("Tvoje cislo hraca: %d\n",idPlayer);
        printf("Cakaj na ostatnych hracov a zaciatok hry!\n");

        closeSocket();
        //vytvorenie hry hraca
        game = new Console(numberOfPlayers);
    }

}

void Client::startGame() {
    //
}

void Client::closeSocket() {
    if (open)
        close(sockfd);
}

Client::~Client() {
    delete game;
}


