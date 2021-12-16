#include "server.h"

Server::Server(int port) {
    open = true;
    numberOfPlayers = 0;
    bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);
    data = {1,0,0, false, 0};
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

void Server::communication() {
    if (open) {
        bzero(buffer,256);
        n = read(newsockfd, buffer, 255);
        if (n < 0)
        {
            perror("Error reading from socket");
            return;
        }
        printf("Here is the message: %s\n", buffer);

        const char* msg = "I got your message";
        n = write(newsockfd, msg, strlen(msg)+1);
        if (n < 0)
        {
            perror("Error writing to socket");
            return;
        }
    }
}

void Server::hra() {
    pthread_t server;
    pthread_t hraci[numberOfPlayers];

    pthread_mutex_t mutex;
    pthread_cond_t jeHodene;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&jeHodene, NULL);

    pthread_create(&server, NULL, reinterpret_cast<void *(*)(void *)>(&update), &data);
    for (int i = 0; i < numberOfPlayers; i++) {
        pthread_create(&hraci[i], NULL, reinterpret_cast<void *(*)(void *)>(&Server::tah), &data);
    }

    pthread_join(server, NULL);
    for (int i = 0; i < numberOfPlayers; i++) {
        pthread_join(hraci[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&jeHodene);
}

void Server::hodKockou() {
    data.poslednyHod = 1 + rand() % 6;
}

void* Server::tah(int parHrac) {
    while (!data.jeVyherca) {
        pthread_mutex_lock(data.mutex);
        while (niecooooooasdgaosdfgpasdfgh) {
            pthread_cond_wait(data.jeHodene, data.mutex);
        }
        //todo posli update kto, s kym, o kolko....

        pthread_mutex_unlock(data.mutex);
        pthread_cond_broadcast(data.jeOdohrane);
    }
    return NULL;
}

void* Server::update(int parHrac) {
    while (!data.jeVyherca) {
        pthread_mutex_lock(data.mutex);
        while (niecooooooooaodsgvoaufdshvoajhf) {
            pthread_cond_wait(data.jeOdohrane, data.mutex);
        }
        data.tahID++;
        data.jeNaTahu = 1 + data.tahID % 4;
        data.poslednyHod = 1 + rand() % 6;
        pthread_mutex_unlock(data.mutex);
        pthread_cond_broadcast(data.jeHodene);
    }
}

void Server::closeSocket() {
    close(newsockfd);
    close(sockfd);
}

Server::~Server() {
}
