#include <iostream>
#include <pthread.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct data {
    int numberOfPlayers;
    int actualPlayer;
    int movingFigure;
    int rollDice;
    bool gameIsEnd;
    int moveID;
    int numberOfUpdates;
    int* newsockfdBuffer;
    char* buffer;
    pthread_mutex_t* mutex;
    pthread_cond_t* moveEnd;
    pthread_cond_t* gameStart;
    pthread_cond_t* updateEnd;
} DATA;

void* hra (void* arg) {
    DATA* data = (DATA*) arg;
    int idPlayer = data->actualPlayer;
    pthread_mutex_lock(data->mutex);
    pthread_cond_wait(data->gameStart, data->mutex);
    pthread_mutex_unlock(data->mutex);
    while(!data->gameIsEnd) {
        if (data->actualPlayer == idPlayer) {
            //tah
            if (data->moveID != 1) {
                while(data->numberOfUpdates != (data->numberOfPlayers - 1)) {
                    pthread_cond_wait(data->updateEnd, data->mutex);
                }
            }
            data->updateEnd = 0;
            data->rollDice = 1 + rand() % 6;
            const char* message = ("1/" + std::to_string(data->rollDice)).c_str();
            int n = write(data->newsockfdBuffer[idPlayer], message, strlen(message) + 1);
            if (n < 0) {
                perror("error writing to socket");
                return NULL;
            }
            bzero(data->buffer, 256);
            n = read(data->newsockfdBuffer[idPlayer], data->buffer, 255);
            if (n < 0) {
                perror("error reading from socket");
                return NULL;
            }
            data->movingFigure = atoi(&data->buffer[0]);
            data->gameIsEnd = atoi(&data->buffer[2]);
            std::cout << "Ťah bol ukončený, posunul sa hráč: " << idPlayer<< ", s figúrkou číslo: " <<
                      data->movingFigure << " o: " << data->rollDice << std::endl;
            //zmena dalsieho hraca
            data->actualPlayer = 1 + data->moveID % data->numberOfPlayers;
            data->moveID++;

            pthread_mutex_unlock(data->mutex);
            pthread_cond_broadcast(data->moveEnd);
        } else {
            //update
            pthread_cond_wait(data->moveEnd, data->mutex);
            const char* message = ("2/" + std::to_string(data->actualPlayer) + "/" + std::to_string(data->movingFigure) + "/" + std::to_string(data->rollDice)).c_str();
            int n = write(data->newsockfdBuffer[idPlayer], message, strlen(message) + 1);
            if (n < 0) {
                perror("error writing to socket");
                return NULL;
            }
            data->numberOfUpdates ++;
            pthread_mutex_unlock(data->mutex);
            pthread_cond_broadcast(data->updateEnd);
        }
    }
    close(data->newsockfdBuffer[idPlayer]);
    return NULL;
}
int main(int argc, char* argv[]) {
    srand(time(nullptr));

    //// atributes
    int sockfd, newsockfd;
    socklen_t cli_len;
    struct sockaddr_in serv_addr;
    struct sockaddr_in cli_addr;
    int n;
    char buffer[256];
    int numberOfPlayers;
    int lastPlayerId = 0;

    //nadstavenie poctu hracov
    if (argc < 1) {
        numberOfPlayers = 2;
    } else {
        numberOfPlayers = atoi(argv[1]);
        if (numberOfPlayers > 4)
            numberOfPlayers = 4;
    }
    printf("Pocet ocakavanych hracov v spustenej hre LUDO: %d", numberOfPlayers);

    int newsockfdBuffer[numberOfPlayers];

    //inicializacia
    bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(9999);

    pthread_mutex_t mutex;
    pthread_cond_t moveEnd;
    pthread_cond_t gameStart;
    pthread_cond_t updateEnd;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&moveEnd, NULL);
    pthread_cond_init(&gameStart, NULL);
    pthread_cond_init(&updateEnd, NULL);

    ////threads
    pthread_t hrac[numberOfPlayers];

    DATA data = {numberOfPlayers, 1, 0, 0, false, 1, 0, newsockfdBuffer, buffer, &mutex, &moveEnd, &gameStart, &updateEnd};

    //Socket communication
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        return 1;
    }

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error binding socket address");
        return 2;
    }

    while(!data.gameIsEnd) {
        bool workWithSocket = true;
        listen(sockfd, 5);
        cli_len = sizeof(cli_addr);
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &cli_len);
        if (newsockfd < 0) {
            perror("ERROR on accept");
            workWithSocket = false;
        }
        if (workWithSocket) {
            bzero(buffer, 256);
            n = read(newsockfd, buffer, 255);
            if (n < 0) {
                perror("Error reading from socket");
                workWithSocket = false;
            }
        }
        if (workWithSocket) {
            if (numberOfPlayers != lastPlayerId) {
                lastPlayerId++;
                const char *message = (std::to_string(numberOfPlayers) + "/" + std::to_string(lastPlayerId)).c_str();
                n = write(newsockfd, message, strlen(message) + 1);
                if (n < 0) {
                    perror("error writing to socket");
                    lastPlayerId--;
                    workWithSocket = false;
                }
                if (workWithSocket) {
                    pthread_mutex_lock(data.mutex);
                    data.newsockfdBuffer[lastPlayerId] = newsockfd;
                    pthread_mutex_unlock(data.mutex);

                    pthread_create(&hrac[lastPlayerId - 1], NULL, &hra, &data);
                    //mozno nefunguje a treba prestudovat atributy vlakna
                    pthread_join(hrac[lastPlayerId-1], NULL);

                    if (lastPlayerId == numberOfPlayers) {
                        pthread_cond_broadcast(data.gameStart);
                    }

                }
            }
        }

    }
    close(sockfd);
    pthread_cond_destroy(&gameStart);
    pthread_cond_destroy(&moveEnd);
    pthread_cond_destroy(&updateEnd);
    pthread_mutex_destroy(&mutex);
    return 0;
}