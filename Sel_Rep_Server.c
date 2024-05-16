#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define MAX_PACKET_SIZE 1024
#define WINDOW_SIZE 4

// Structure to represent a packet
struct packet {
    int seq_num;
    char data[MAX_PACKET_SIZE];
};

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to localhost and port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        struct packet recv_packet;
        // Receive packet
        if (recvfrom(server_fd, &recv_packet, sizeof(recv_packet), 0, (struct sockaddr *)&address, (socklen_t*)&addrlen) < 0) {
            perror("recvfrom failed");
            exit(EXIT_FAILURE);
        }

        // Process received packet
        printf("Received Packet with Sequence Number: %d\n", recv_packet.seq_num);

        // Send ACK back to the client
        sendto(server_fd, &recv_packet.seq_num, sizeof(recv_packet.seq_num), 0, (struct sockaddr *)&address, addrlen);
    }

    return 0;
}

