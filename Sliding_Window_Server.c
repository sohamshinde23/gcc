#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8000

int main()
{
    char servermessage[256];
    struct sockaddr_in serveraddress, clientaddress;
    int client_address_len = sizeof(clientaddress);

    int serversocket;
    serversocket = socket(AF_INET, SOCK_STREAM, 0); 
    if(serversocket < 0)
    {
        printf("socket failed");
        return -1;
    }

    serveraddress.sin_family = AF_INET;
    serveraddress.sin_port = htons(PORT);
    serveraddress.sin_addr.s_addr = INADDR_ANY;

    int bindstatus;
    bindstatus = bind(serversocket, (const struct sockaddr*)&serveraddress, sizeof(serveraddress));
    if (bindstatus < 0)
    {
        printf("binding failed\n");
        return -1;
    }
    else
    {
        printf("binding is successful\n");
    }

    listen(serversocket, 3);
    printf("Waiting for client connection...\n");

    int clientsocket;
    clientsocket = accept(serversocket, (struct sockaddr *)&clientaddress, (socklen_t *)&client_address_len);
    if(clientsocket<0)
    {
        printf("connection is rejected by server\n");
        return -1;
    } 
    else
        printf("connection is accepted\n");

    int n, f, j;
    recv(clientsocket, &n, sizeof(n), 0);
    recv(clientsocket, &f, sizeof(f), 0);
    
    int ack = 0; // Initialize acknowledgment

    for(int k = 0; k < n; k++)
    {
        recv(clientsocket, &j, sizeof(j), 0);
        printf("\nreceived bit: %d", j);

        // Send acknowledgment for each bit received
        send(clientsocket, &ack, sizeof(ack), 0);
        ack++;
    }

    printf("\nfinished\n");

    close(clientsocket);
    close(serversocket);

    return 0;
}

