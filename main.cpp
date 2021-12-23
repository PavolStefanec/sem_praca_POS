#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include "Header_files/interface.h"

using namespace std;

int main(int argc, char* args[]) {
    int sockfd;
    int n;
    struct sockaddr_in serv_addr;
    struct hostent* server;
    char buffer[256];

    int idPlayer = 0;
    int numberOfPlayers = 0;
    Interface* game = nullptr;
    bool gameIsPlaying = true;

    server = gethostbyname("localhost");
    if (server == NULL) {
        fprintf(stderr, "Error, no such host\n");
        return 1;
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy(
            (char *) server->h_addr,
            (char *) &serv_addr.sin_addr.s_addr,
            server->h_length
    );

    std::cout << "zadajte cislo portu: " << std::endl;
    std::string input;
    std::cin >> input;
    int inputInt = stoi(input);
    if (inputInt < 1024 || inputInt > 49151) {
        std::cout << "neplatne cislo portu" << std::endl;
        return 10;
    }

    serv_addr.sin_port = htons(atoi(input.c_str()));

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        return 2;
    }

    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) != 0) {
        perror("Error connecting to socket");
        return 3;
    }

    //pripojenie do hry
    std::cout << "Pripajanie do hry..." << std::endl;
    bzero(buffer, 256);
    n = read(sockfd, buffer, 255);
    if (n < 0) {
        perror("Error reading from socket");
        close(sockfd);
        return 4;
    }
    numberOfPlayers = std::atoi(&buffer[0]);
    idPlayer = std::atoi(&buffer[2]);
    printf("Si v hre!\n");
    std::cout << "Celkový počet hráčov v hre: " << numberOfPlayers << std::endl;
    printf("Tvoje číslo hráča: %d\n", idPlayer);
    game = new Interface(numberOfPlayers);
    game->start();
    game->drawBoard();
    //verzia pre rychle ukoncenie hry
//    int counter = 0;
//    while(counter < 4) {
    while(gameIsPlaying) {
            bzero(buffer, 256);
            n = read(sockfd, buffer, 255);
            if (n < 0) {
                perror("Error reading from socket");
                return 5;
            }
            int acctionType = atoi(&buffer[0]);
            if (acctionType == 1) {
                //rychle ukoncenie hry
//                counter++;
                game->setActivePlayer(idPlayer);
                int value = atoi(&buffer[2]);
                int figure = game->getNumberOfPiece(value);
                if (figure > 0 && figure < 5) {
                    game->move(value, figure);
                }
                game->drawBoard();
                int isWinner = 0;
                if (game->isEnd()) {
                    cout << "\033[1;" << COLOR_NUMBER + idPlayer - 1
                         << "m GRATULUJEME! Vyhral si!: \033[0m";
                    gameIsPlaying = false;
                    isWinner = 1;
                }
                const char *figureCH = (std::to_string(figure) + "/" + std::to_string(isWinner)).c_str();
                n = write(sockfd, figureCH, strlen(figureCH) + 1);
                if (n < 0) {
                    perror("Error writing to socket");
                    return 6;
                }
            } else {
                int movingPlayer = atoi(&buffer[2]);
                int figure = atoi(&buffer[4]);
                int number = atoi(&buffer[6]);
                if (figure != 0) {
                    game->setActivePlayer(movingPlayer);
                    game->move(number, figure);
                    game->drawBoard();
                    if (game->isEnd()) {
                        cout << "\033[1;" << COLOR_NUMBER + idPlayer - 1
                             << "m Víťazom sa stáva hráč číslo: \033[0m";
                        cout << "\033[1;" << COLOR_NUMBER + movingPlayer - 1 << "m " << movingPlayer
                             << "\033[0m" << endl;
                        cout << "\033[1;" << COLOR_NUMBER + idPlayer - 1
                             << "m Žiaľ, tebe to dnes nevyšlo, možno nabudúce! \033[0m";
                        gameIsPlaying = false;
                    }
                } else {
                    cout<<"\033[1;" << COLOR_NUMBER + movingPlayer - 1 <<"m Hráč preskakuje ťah! \033[0m"<<endl;
                    game->drawBoard();
                }
            }
        }
        close(sockfd);
    if (game)
        delete game;
    return 0;
}