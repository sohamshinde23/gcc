#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8000
#define MAX_DATA_SIZE 100

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main() {
    int serversocket, clientsocket;
    struct sockaddr_in serveraddress, clientaddress;
    socklen_t client_address_len;

    char data[MAX_DATA_SIZE];
    int k, count = 0, j = 1;

    // Create socket
    serversocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serversocket < 0)
        error("Error opening socket");

    // Initialize server address
    bzero((char *) &serveraddress, sizeof(serveraddress));
    serveraddress.sin_family = AF_INET;
    serveraddress.sin_addr.s_addr = INADDR_ANY;
    serveraddress.sin_port = htons(PORT);

    // Bind socket to address
    if (bind(serversocket, (struct sockaddr *) &serveraddress, sizeof(serveraddress)) < 0)
        error("Error on binding");

    // Listen for connections
    listen(serversocket, 5);
    printf("Waiting for client connection...\n");

    // Accept client connection
    client_address_len = sizeof(clientaddress);
    clientsocket = accept(serversocket, (struct sockaddr *) &clientaddress, &client_address_len);
    if (clientsocket < 0)
        error("Error on accept");

    printf("Connection established with client.\n");

    // Receive length of data from client
    recv(clientsocket, &k, sizeof(k), 0);

    // Receive data from client
    for (int i = 0; i < k; i++) {
        recv(clientsocket, &data[i], sizeof(data[i]), 0);
        printf("Received bit %d from client\n", i + 1);

        // Send acknowledgment to client
        send(clientsocket, &j, sizeof(j), 0);
        j++;
    }

    printf("\nData received from the client is: %s\n", data);

    // Close sockets
    close(clientsocket);
    close(serversocket);

    return 0;
}

