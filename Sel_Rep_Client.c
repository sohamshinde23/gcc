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
    int sock;
    struct sockaddr_in server_addr;
    struct packet send_packet, recv_ack;

    // Create socket
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Client loop
    int next_seq_num = 0;
    while (1) {
        printf("Enter data to send: ");
        fgets(send_packet.data, MAX_PACKET_SIZE, stdin);
        send_packet.seq_num = next_seq_num;
        send_packet.data[strlen(send_packet.data)-1] = '\0'; // Removing newline character

        // Send packet
        if (sendto(sock, &send_packet, sizeof(send_packet), 0, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
            perror("sendto failed");
            exit(EXIT_FAILURE);
        }

        // Receive ACK
        if (recvfrom(sock, &recv_ack, sizeof(recv_ack), 0, NULL, NULL) < 0) {
            perror("recvfrom failed");
            exit(EXIT_FAILURE);
        }

        // Process ACK
        printf("Received ACK for Sequence Number: %d\n", recv_ack.seq_num);

        // Move to the next sequence number
        next_seq_num++;
    }

    close(sock);
    return 0;
}

