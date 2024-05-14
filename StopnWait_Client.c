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
    exit(0);
}

int main() {
    int clientsocket;
    struct sockaddr_in serveraddress;
    char data[MAX_DATA_SIZE];
    int k, count = 0;

    // Create socket
    clientsocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientsocket < 0)
        error("Error opening socket");

    // Initialize server address
    bzero((char *) &serveraddress, sizeof(serveraddress));
    serveraddress.sin_family = AF_INET;
    serveraddress.sin_port = htons(PORT);
    serveraddress.sin_addr.s_addr = INADDR_ANY;

    // Connect to server
    if (connect(clientsocket, (struct sockaddr *) &serveraddress, sizeof(serveraddress)) < 0)
        error("Error connecting");

    printf("Connection established with server.\n");

    // Enter data
    printf("Enter the data: ");
    fgets(data, MAX_DATA_SIZE, stdin);
    data[strcspn(data, "\n")] = '\0'; // Remove trailing newline

    // Send length of data to server
    k = strlen(data);
    send(clientsocket, &k, sizeof(k), 0);

    // Send data to server
    for (int i = 0; i < k; i++) {
        send(clientsocket, &data[i], sizeof(data[i]), 0);
        recv(clientsocket, &count, sizeof(count), 0);
        printf("Acknowledgment received for bit %d from server\n", i + 1);
    }

    // Close socket
    close(clientsocket);

    return 0;
}

