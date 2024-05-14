#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100
#define SIGNAL_SIZE 110

void generate_signal(const char data[], char signal[]);
void xnor_encode(const char signal[], char result[]);
void decode_signal(const char encoded[], char decoded[]);

int main() {
    char data[MAX_SIZE];
    char signal[SIGNAL_SIZE];
    char encoded[SIGNAL_SIZE];
    char decoded[MAX_SIZE];

    printf("Enter Data: ");
    scanf("%s", data);

    generate_signal(data, signal);
    printf("Generated Signal: %s\n", signal);

    xnor_encode(signal, encoded);
    printf("Encoded Signal: %s\n", encoded);

    decode_signal(encoded, decoded);
    printf("Decoded Data: %s\n", decoded);

    return 0;
}

void generate_signal(const char data[], char signal[]) {
    int k = 0;
    for (int i = 0; i < strlen(data); i++) {
        if (data[i] == '1') {
            for (int j = 0; j < 11; j++) {
                signal[k++] = '1';
            }
        } else {
            for (int j = 0; j < 11; j++) {
                signal[k++] = '0';
            }
        }
    }
    signal[k] = '\0'; // Null termination
}

void xnor_encode(const char signal[], char result[]) {
    char pattern[] = {'1', '0', '1', '1', '0', '1', '1', '1', '0', '0', '0'};
    int l = strlen(signal) / 11;
    int k = 0;
    while (l > 0) {
        for (int i = 0; i < 11; i++) {
            if (signal[k] == pattern[i]) {
                result[k++] = '1';
            } else {
                result[k++] = '0';
            }
        }
        l--;
    }
    result[k] = '\0'; // Null termination
}
void decode_signal(const char encoded[], char decoded[]) {
    int k = 0, j = 0;
    int l = strlen(encoded);
    while (k < l) {
        int flag = 0; // Reset flag for each 11-bit sequence
        for (int i = 0; i < 11; i++) {
            if (encoded[k++] == '1') {
                flag++;
            }
        }
        decoded[j++] = (flag >= 6) ? '1' : '0'; // Use majority logic
    }
    decoded[j] = '\0'; // Null termination
}

/*
Enter Data: 1010

Output:

Generated Signal: 11111111111000000000001111111111100000000000
Encoded Signal: 10110111000010010001111011011100001001000111
Decoded Data: 1010


*/

