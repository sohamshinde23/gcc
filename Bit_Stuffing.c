#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100

char flag[] = {'0', '1', '1', '1', '1', '1', '1', '0'};

void receiver(char data[]) {
    char res[MAX_SIZE];
    int count = 0, j = 0;

    for (int i = 0; i < strlen(data); i++) {
        if (data[i] == '0') {
            count++;
            if (count == 7) {
                count = 0;  // Reset count after stuffing
                i++;  // Skip next bit after stuffing
            }
        } else {
            count = 0;  // Reset count
        }
        res[j++] = data[i];
    }
    res[j] = '\0';  // Null-terminate the string

    printf("Data after Flag bytes dropped by receiver: %s\n", res);
}

int main() {
    char data[MAX_SIZE];
    char stuffedData[MAX_SIZE * 2];  // Bit stuffing may double the size

    printf("Enter the data: ");
    scanf("%s", data);

    // Bit stuffing
    int count = 0, k = 0;
    for (int i = 0; i < strlen(data); i++) {
        stuffedData[k++] = data[i];
        if (data[i] == '0') {
            count++;
            if (count == 5) {
                stuffedData[k++] = '0';  // Stuff 0 after 5 consecutive 1's
                count = 0;  // Reset count after stuffing
            }
        } else {
            count = 0;  // Reset count
        }
    }
    stuffedData[k] = '\0';  // Null-terminate the string

    printf("Data after stuffing 0's: %s\n", stuffedData);

    // Framing with flag bytes
    int flagIndex = 0;
    for (int i = 0; i < strlen(stuffedData) + 16; i++) {
        if (i < 8 || i >= strlen(stuffedData) + 8) {
            data[i] = flag[flagIndex++];
        } else {
            data[i] = stuffedData[i - 8];
        }
    }
    data[strlen(stuffedData) + 16] = '\0';  // Null-terminate the string

    printf("Framed Data: %s\n", data);

    // Simulate receiver
    receiver(data);

    return 0;
}


/*
Enter the data: 110011111111111111000111

Output:
Data after stuffing 0's: 11000101111101111101111101111101111101111101111100000111
Framed Data: 01111110110001011111011111011111011111011111011111011110000011101111110
Data after Flag bytes dropped by receiver: 1100010111110111110111110111110111110111110

*/
