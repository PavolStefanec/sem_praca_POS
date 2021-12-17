#include <iostream>
#include <pthread.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
//#include "server.h"

typedef struct data {
    int jeNaTahu;
    int posuvaSaPanak;
    int poslednyHod;
    bool jeVyherca;
    int tahID;
    bool zahralTah;

    pthread_mutex_t* mutex;
    pthread_cond_t* jeHodene;
    pthread_cond_t* jeOdohrane;
} DATA;

void* update(void* parData) {
    DATA* data = (DATA*) parData;
    while (!data->jeVyherca) {
        pthread_mutex_lock(data->mutex);
        while (!data->zahralTah) {
            pthread_cond_wait(data->jeOdohrane, data->mutex);
        }
        data->jeNaTahu = 1 + data->tahID % 4;
        data->tahID++;
        data->poslednyHod = 1 + rand() % 6;
        //todo poslat hracom info
        pthread_mutex_unlock(data->mutex);
        pthread_cond_broadcast(data->jeHodene);
    }
    return nullptr;
}

void* tah(void *parData) {
    DATA* data = (DATA*) parData;
    while (!data->jeVyherca) {
        pthread_mutex_lock(data->mutex);
        while (true) {
            pthread_cond_wait(data->jeHodene, data->mutex);
        }
        //todo posli update kto, s kym, o kolko....

        pthread_mutex_unlock(data->mutex);
        pthread_cond_broadcast(data->jeOdohrane);
    }
    return nullptr;
}


int main() {
//    Server* server = new Server(9999, 1);
//    server->creatingSocket();
//    server->binding();
//    server->connectPlayerToGame();
//    server->closeSocket();
//    delete server;

    int sockfd, newsockfd;
    socklen_t cli_len;
    //server
    struct sockaddr_in serv_addr;
    //klienti
    struct sockaddr_in cli_addr;
    int n;
    char buffer[256];
    bool open;
    int numberOfPlayers;
    int lastPlayerId;

    open = true;
    numberOfPlayers = 2;
    bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(9999);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        open = false;
    }

    if (open) {
        if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
            perror("Error binding socket address");
            open = false;
        }
    }

    listen(sockfd, 5);
    cli_len = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &cli_len);
    if (newsockfd < 0) {
        perror("ERROR on accept");
        open = false;
    }

    pthread_t server;
    pthread_t hraci[numberOfPlayers];

    pthread_mutex_t mutex;
    pthread_cond_t jeHodene;
    pthread_cond_t jeOdohrane;

    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&jeHodene, nullptr);
    pthread_cond_init(&jeOdohrane, nullptr);

    DATA data = {1,0,0, false, 0, true, &mutex, &jeHodene, &jeOdohrane};

    pthread_create(&server, nullptr, &update, &data);
    for (int i = 0; i < numberOfPlayers; i++) {
        pthread_create(&hraci[i], nullptr, &tah, &data);
    }

    pthread_join(server, nullptr);
    for (int i = 0; i < numberOfPlayers; i++) {
        pthread_join(hraci[i], nullptr);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&jeHodene);
    pthread_cond_destroy(&jeOdohrane);

    return 0;
}




//// inet_addr
//#include <arpa/inet.h>
//
//// For threading, link with lpthread
//#include <pthread.h>
//#include <semaphore.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <sys/socket.h>
//#include <unistd.h>
//
//// Semaphore variables
//sem_t x, y;
//pthread_t tid;
//pthread_t writerthreads[100];
//pthread_t readerthreads[100];
//int readercount = 0;
//
//// Reader Function
//void* reader(void* param)
//{
//    // Lock the semaphore
//    sem_wait(&x);
//    readercount++;
//
//    if (readercount == 1)
//        sem_wait(&y);
//
//    // Unlock the semaphore
//    sem_post(&x);
//
//    printf("\n%d reader is inside",
//           readercount);
//
//    sleep(5);
//
//    // Lock the semaphore
//    sem_wait(&x);
//    readercount--;
//
//    if (readercount == 0) {
//        sem_post(&y);
//    }
//
//    // Lock the semaphore
//    sem_post(&x);
//
//    printf("\n%d Reader is leaving",
//           readercount + 1);
//    pthread_exit(NULL);
//}
//
//// Writer Function
//void* writer(void* param)
//{
//    printf("\nWriter is trying to enter");
//
//    // Lock the semaphore
//    sem_wait(&y);
//
//    printf("\nWriter has entered");
//
//    // Unlock the semaphore
//    sem_post(&y);
//
//    printf("\nWriter is leaving");
//    pthread_exit(NULL);
//}
//
//// Driver Code
//int main()
//{
//    // Initialize variables
//    int serverSocket, newSocket;
//    struct sockaddr_in serverAddr;
//    struct sockaddr_storage serverStorage;
//
//    socklen_t addr_size;
//    sem_init(&x, 0, 1);
//    sem_init(&y, 0, 1);
//
//    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
//    serverAddr.sin_addr.s_addr = INADDR_ANY;
//    serverAddr.sin_family = AF_INET;
//    serverAddr.sin_port = htons(8989);
//
//    // Bind the socket to the
//    // address and port number.
//    bind(serverSocket,
//         (struct sockaddr*)&serverAddr,
//         sizeof(serverAddr));
//
//    // Listen on the socket,
//    // with 40 max connection
//    // requests queued
//    if (listen(serverSocket, 50) == 0)
//        printf("Listening\n");
//    else
//        printf("Error\n");
//
//    // Array for thread
//    pthread_t tid[60];
//
//    int i = 0;
//
//    while (1) {
//        addr_size = sizeof(serverStorage);
//
//        // Extract the first
//        // connection in the queue
//        newSocket = accept(serverSocket,
//                           (struct sockaddr*)&serverStorage,
//                           &addr_size);
//        int choice = 0;
//        recv(newSocket,
//             &choice, sizeof(choice), 0);
//
//        if (choice == 1) {
//            // Creater readers thread
//            if (pthread_create(&readerthreads[i++], NULL,
//                               reader, &newSocket)
//                != 0)
//
//                // Error in creating thread
//                printf("Failed to create thread\n");
//        }
//        else if (choice == 2) {
//            // Create writers thread
//            if (pthread_create(&writerthreads[i++], NULL,
//                               writer, &newSocket)
//                != 0)
//
//                // Error in creating thread
//                printf("Failed to create thread\n");
//        }
//
//        if (i >= 50) {
//            // Update i
//            i = 0;
//
//            while (i < 50) {
//                // Suspend execution of
//                // the calling thread
//                // until the target
//                // thread terminates
//                pthread_join(writerthreads[i++],
//                             NULL);
//                pthread_join(readerthreads[i++],
//                             NULL);
//            }
//
//            // Update i
//            i = 0;
//        }
//    }
//
//    return 0;
//}