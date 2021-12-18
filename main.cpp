#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include "Header_files/console.h"

using namespace std;

int main(int argc, char* args[]) {
    int sockfd;
    int n;
    struct sockaddr_in serv_addr;
    struct hostent* server;
    bool open;
    char buffer[256];

    int idPlayer = 0;
    int numberOfPlayers = 0;
    Console* game;
    bool connected;
    bool gameIsPlaying = true;
    while(gameIsPlaying) {
        connected = true;
        server = gethostbyname("localhost");
        if (server == NULL) {
            fprintf(stderr, "Error, no such host\n");
            connected = false;
        }

        if (connected) {
            bzero((char *) &serv_addr, sizeof(serv_addr));
            serv_addr.sin_family = AF_INET;
            bcopy(
                    (char *) server->h_addr,
                    (char *) &serv_addr.sin_addr.s_addr,
                    server->h_length
            );
            serv_addr.sin_port = htons(9999);

            sockfd = socket(AF_INET, SOCK_STREAM, 0);
            if (sockfd < 0) {
                perror("Error creating socket");
                connected = false;
            }
        }

        if (connected) {
            if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) != 0) {
                perror("Error connecting to socket");
                connected = false;
            }
        }

        if (connected) {
            const char *idPlayerCh = std::to_string(idPlayer).c_str();
            n = write(sockfd, idPlayerCh, strlen(idPlayerCh));
            if (n < 0) {
                perror("Error writing to socket");
                close(sockfd);
                break;
            }

            if (idPlayer == 0) {
                std::cout << "Pripajanie do hry..." << std::endl;
                bzero(buffer, 256);
                n = read(sockfd, buffer, 255);
                if (n != 0) {
                    perror("Error reading from socket");
                    close(sockfd);
                    break;
                }
                numberOfPlayers = atoi(reinterpret_cast<const char *>(buffer[0]));
                idPlayer = atoi(reinterpret_cast<const char *>(buffer[1]));
                printf("Si v hre!\n");
                std::cout << "Celkovy pocet hracov v hre: " << numberOfPlayers << std::endl;
                printf("Tvoje cislo hraca: %d\n", idPlayer);
                game = new Console(numberOfPlayers);
                game->start();
            } else {
                bzero(buffer, 256);
                n = read(sockfd, buffer, 255);
                if (n != 0) {
                    perror("Error reading from socket");
                    close(sockfd);
                    break;
                }
                int activePlayer = atoi(reinterpret_cast<const char *>(buffer[0]));
                if (activePlayer == 0) {
                    printf("Hra sa este nezacala!\n");
                } else {
                    game->setActivePlayer(activePlayer);
                    if (activePlayer == idPlayer) {
                        //si na tahu
                        int figure = game->getNumberOfPiece();
                        if (figure > 0 && figure < 5)
                            game->move(atoi(reinterpret_cast<const char *>(buffer[1])), figure);
                        else
                            figure = 0;
                        const char *figureCH = std::to_string(figure).c_str();
                        n = write(sockfd, figureCH, strlen(figureCH));
                        if (n < 0) {
                            perror("Error writing to socket");
                            close(sockfd);
                            break;
                        }
                        game->drawBoard();
                        if (game->isEnd()) {
                            cout << "\033[1;" << COLOR_NUMBER + activePlayer - 1
                                 << "m GRATULUJEME! Vyhral si!: \033[0m";
                            gameIsPlaying = false;
                        }
                    } else {
                        //update
                        int figure = atoi(reinterpret_cast<const char *>(buffer[1]));
                        int number = atoi(reinterpret_cast<const char *>(buffer[2]));
                        if (figure != 0) {
                            game->setActivePlayer(activePlayer);
                            game->move(numberOfPlayers, figure);
                            game->drawBoard();
                            if (game->isEnd()) {
                                cout << "\033[1;" << COLOR_NUMBER + idPlayer - 1
                                     << "m Víťazom sa stáva hráč číslo: \033[0m";
                                cout << "\033[1;" << COLOR_NUMBER + activePlayer - 1 << "m " << activePlayer
                                     << "\033[0m" << endl;
                                cout << "\033[1;" << COLOR_NUMBER + idPlayer - 1
                                     << "m Žiaľ, tebe to dnes nevyšlo, možno nabudúce! \033[0m";
                                gameIsPlaying = false;
                            }
                        }
                    }
                }

            }
            close(sockfd);
        }
        sleep(0.25);
    }
    return 0;
}