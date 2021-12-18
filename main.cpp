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
    int jeNaTahu;
    int pripojenyHrac;
    int posuvaSaPanak;
    int poslednyHod;
    int pocetHracov;
    bool jeVyherca;
    int tahID;
    int socket;
    char* buffer;
    bool* updates;

    pthread_mutex_t* mutex;
} DATA;

void* update(void* parData) {
    DATA* data = (DATA*) parData;

    int n = -1;
    int counter = 0;
    const char *message;
    message = (std::to_string(data->jeNaTahu) + "/" + std::to_string(data->posuvaSaPanak) + "/"
               + std::to_string(data->poslednyHod)).c_str();
    while (n < 0) {
        counter++;
        if (counter > 5) {
            std::cerr << "player is not responding" << std::endl;
            break;
        }
        pthread_mutex_lock(data->mutex);
        n = write(data->socket, message, strlen(message) + 1);
        if (n < 0) {
            perror("error writing to socket");
            sleep(static_cast<unsigned long>(0.25));
        } else
            data->updates[data->pripojenyHrac - 1] = true;
        pthread_mutex_unlock(data->mutex);
    }
    return nullptr;
}

void* tah(void *parData) {
    DATA* data = (DATA*) parData;

    int n = -1;
    int counter = 0;
    pthread_mutex_lock(data->mutex);
    data->poslednyHod = 1 + rand() % 6;
    const char* message = (std::to_string(data->jeNaTahu) + "/" + std::to_string(data->poslednyHod)).c_str();
    while (n < 0) {
        counter++;
        if (counter > 5) {
            std::cerr << "player is not responding" << std::endl;
            break;
        }
        n = write(data->socket, message, strlen(message) + 1);
        if (n < 0) {
            perror("error writing to socket");
            sleep(static_cast<unsigned long>(0.25));
        } else {
            bzero(data->buffer, 256);
            n = read(data->socket, data->buffer, 255);
            if (n < 0) {
                perror("error reading from socket");
                sleep(static_cast<unsigned long>(0.25));
            } else {
                data->posuvaSaPanak = atoi(&data->buffer[0]);
                data->jeVyherca = atoi(&data->buffer[2]);

                std::cout << "tah bol ukonceny, posunul sa hrac " << data->jeNaTahu << ", s panakom " <<
                          data->posuvaSaPanak << ", o " << data->poslednyHod << " policka" << std::endl;
                data->updates[data->jeNaTahu - 1] = true;
            }
        }
    }
    pthread_mutex_unlock(data->mutex);
    return nullptr;
}

int main() {

    srand(time(nullptr));
    //// atributes
    int sockfd, newsockfd;
    socklen_t cli_len;
    struct sockaddr_in serv_addr;
    struct sockaddr_in cli_addr;
    int n;
    char buffer[256];
    int pocetHracov = 2;
    bool updatedAll[pocetHracov];
    int lastPlayerId = 0;

    bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(9999);


    ////mutex initialization
    pthread_mutex_t mutex;
    pthread_cond_t jeHodene;
    pthread_cond_t jeOdohrane;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&jeHodene, NULL);
    pthread_cond_init(&jeOdohrane, NULL);

    ////threads
    pthread_t hrac;

    DATA data = {1, 0, 0, 0, pocetHracov, false, 0, 0, buffer, updatedAll, &mutex};

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        return 1;
    }

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error binding socket address");
        return 2;
    }

    while (lastPlayerId != pocetHracov) {
        listen(sockfd, 5);
        cli_len = sizeof(cli_addr);
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &cli_len);
        if (newsockfd < 0) {
            perror("ERROR on accept");
            return 3;
        } else {
            bzero(buffer, 256);
            n = read(newsockfd, buffer, 255);
            if (n < 0) {
                perror("Error reading from socket");
                return 7;
            }

            if (atoi(&buffer[0]) == 0) {
                lastPlayerId++;
                const char* message = (std::to_string(pocetHracov) + "/" + std::to_string(lastPlayerId)).c_str();
                n = write(newsockfd, message, strlen(message) + 1);
                if (n < 0) {
                    perror("error writing to socket");
                    lastPlayerId--;
                }
            } else {
                const char* message = "0/0/0";
                n = write(newsockfd, message, strlen(message) + 1);
                if (n < 0)
                    perror("error writing to socket");
            }
        }
    }

    while (!data.jeVyherca) {
        listen(sockfd, 5);
        cli_len = sizeof(cli_addr);
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &cli_len);
        if (newsockfd < 0) {
            perror("ERROR on accept");
            return 3;
        } else {
            data.socket = newsockfd;

            bzero(buffer, 256);
            n = read(newsockfd, buffer, 255);
            if (n < 0) {
                perror("Error reading from socket");
                return 4;
            }
            data.pripojenyHrac = atoi(&buffer[0]);
            if (data.pripojenyHrac == data.jeNaTahu && !data.updates[data.pripojenyHrac - 1]) {
                pthread_create(&hrac, NULL, &tah, &data);
                pthread_join(hrac, NULL);
                if (!data.updates[data.pripojenyHrac - 1]) {
                    std::cerr << "player disconnected from the game... GAME OVER" << std::endl;
                    return 9999;
                }
            } else if (!data.updates[data.pripojenyHrac - 1] && data.updates[data.jeNaTahu - 1]) {
                pthread_create(&hrac, NULL, &update, &data);
                pthread_join(hrac, NULL);
                if (!data.updates[data.pripojenyHrac - 1]) {
                    std::cerr << "player disconnected from the game... GAME OVER" << std::endl;
                    return 9999;
                }
                bool updatedAll = true;
                for (int i = 0; i < pocetHracov; i++) {
                    if (!data.updates[i]) {
                        updatedAll = false;
                        break;
                    }
                }
                if (updatedAll) {
                    data.jeNaTahu = 1 + data.tahID % data.pocetHracov;
                    data.tahID++;
                    for (int i = 0; i < pocetHracov; i++) {
                        data.updates[i] = false;
                    }
                }
            }
        } //todo zatvorka tu strajkuje
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&jeHodene);
    pthread_cond_destroy(&jeOdohrane);

    return 0;
}
