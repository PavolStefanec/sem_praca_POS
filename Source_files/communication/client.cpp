#include "../../Header_files/communication/client.h"

Client::Client(char* ipAddress, int parPort) {
    server = gethostbyname(parPort);
    if (server == NULL)
    {
        fprintf(stderr, "Error, no such host\n");
        return;
    }

    bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy(
            (char*)server->h_addr,
            (char*)&serv_addr.sin_addr.s_addr,
            server->h_length
    );
    serv_addr.sin_port = htons(int ipAddress);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Error creating socket");
        return;
    } else {
        perror("Socket successfully created");
    }
}

void Client::connectToServer() {
    if(connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Error connecting to socket");
        return 4;
    }

    printf("Please enter a message: ");
    bzero(buffer,256);
    fgets(buffer, 255, stdin);

    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0)
    {
        perror("Error writing to socket");
        return 5;
    }

    bzero(buffer,256);
    n = read(sockfd, buffer, 255);
    if (n < 0)
    {
        perror("Error reading from socket");
        return 6;
    }

    printf("%s\n",buffer);
    close(sockfd);
}