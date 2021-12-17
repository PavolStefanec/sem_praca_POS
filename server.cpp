//#include "server.h"
//
//Server::Server(int port, int parNumberOfPlayers) {
//    open = true;
//    numberOfPlayers = parNumberOfPlayers;
//    bzero((char*)&serv_addr, sizeof(serv_addr));
//    serv_addr.sin_family = AF_INET;
//    serv_addr.sin_addr.s_addr = INADDR_ANY;
//    serv_addr.sin_port = htons(port);
//}
//
//void Server::creatingSocket() {
//    sockfd = socket(AF_INET, SOCK_STREAM, 0);
//    if (sockfd < 0) {
//        perror("Error creating socket");
//        open = false;
//        return;
//    }
//}
//
//void Server::binding() {
//    if (open) {
//        if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
//            perror("Error binding socket address");
//            open = false;
//            return;
//        }
//    }
//}
//
//void Server::listening() {
//    listen(sockfd, 5);
//    cli_len = sizeof(cli_addr);
//    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &cli_len);
//    if (newsockfd < 0) {
//        perror("ERROR on accept");
//        open = false;
//        return;
//    }
//}
//
//void Server::connectPlayerToGame() {
//    while (lastPlayerId != numberOfPlayers) {
//        listening();
//        if (open) {
//            bzero(buffer, 256);
//            n = read(newsockfd, buffer, 255);
//            if (n < 0) {
//                perror("Error reading from socket");
//                open = false;
//                return;
//            }
//            int message = atoi(buffer);
//            if (message == 0) {
//                const char* number = std::to_string(numberOfPlayers).c_str();
//                n = write(newsockfd, number, strlen(number)+1);
//                if (n < 0)
//                {
//                    perror("Error writing to socket");
//                    open = false;
//                    return;
//                }
//
//                lastPlayerId++;
//                const char* idPlayer = std::to_string(lastPlayerId).c_str();
//                n = write(newsockfd, idPlayer, strlen(idPlayer)+1);
//                if (n < 0)
//                {
//                    perror("Error writing to socket");
//                    open = false;
//                    return;
//                }
//                printf("Do hry sa pripojil hrac s id: %d", lastPlayerId);
//            }
//        }
//    }
//    printf("Vsetci hraci su pripojeny!\nLUDO sa zacina!\n");
//}
//
//void Server::hra() {
//    pthread_t server;
//    pthread_t hraci[numberOfPlayers];
//
//    pthread_mutex_t mutex;
//    pthread_cond_t jeHodene;
//    pthread_cond_t jeOdohrane;
//
//    pthread_mutex_init(&mutex, nullptr);
//    pthread_cond_init(&jeHodene, nullptr);
//    pthread_cond_init(&jeOdohrane, nullptr);
//
//    DATA data = {1,0,0, false, 0, true, &mutex, &jeHodene, &jeOdohrane};
//
//    pthread_create(&server, nullptr, &Server::update, &data);
//    for (int i = 0; i < numberOfPlayers; i++) {
//        pthread_create(&hraci[i], nullptr, &Server::tah, &data);
//    }
//
//    pthread_join(server, nullptr);
//    for (int i = 0; i < numberOfPlayers; i++) {
//        pthread_join(hraci[i], nullptr);
//    }
//
//    pthread_mutex_destroy(&mutex);
//    pthread_cond_destroy(&jeHodene);
//
//}
//
//void* Server::update(void* parData) {
//    DATA* data = (DATA*) parData;
//    while (!data->jeVyherca) {
//        pthread_mutex_lock(data->mutex);
//        while (!data->zahralTah) {
//            pthread_cond_wait(data->jeOdohrane, data->mutex);
//        }
//        data->jeNaTahu = 1 + data->tahID % 4;
//        data->tahID++;
//        data->poslednyHod = 1 + rand() % 6;
//        //todo poslat hracom info
//        pthread_mutex_unlock(data->mutex);
//        pthread_cond_broadcast(data->jeHodene);
//    }
//    return nullptr;
//}
//
//void* Server::tah(void *parData) {
//    DATA* data = (DATA*) parData;
//    while (!data->jeVyherca) {
//        pthread_mutex_lock(data->mutex);
//        while (true) {
//            pthread_cond_wait(data->jeHodene, data->mutex);
//        }
//        //todo posli update kto, s kym, o kolko....
//
//        pthread_mutex_unlock(data->mutex);
//        pthread_cond_broadcast(data->jeOdohrane);
//    }
//    return nullptr;
//}
//
//void Server::closeSocket() {
//    close(newsockfd);
//    close(sockfd);
//}
//
//Server::~Server() {
//}
