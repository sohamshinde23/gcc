#include <stdio.h>
#include <string.h>

#define MAX_DATA_LENGTH 100

// Define flag and escape sequences
char flag[] = {'0', '1', '1', '1', '1', '1', '1', '0'};
char esc[] = {'0', '0', '0', '1', '1', '0', '1', '1'};

// Function to extract original data from framed data
void receiver(char framedData[]) {
    char originalData[MAX_DATA_LENGTH]; // Assuming max length for original data
    int originalIndex = 0;

    // Loop through the framed data to extract original data
    for (int i = 8; i < strlen(framedData) - 8; i++) {
        // Check if the current 8-bit sequence is not the flag sequence
        int isFlag = 1;
        for (int j = 0; j < 8; j++) {
            if (framedData[i+j] != flag[j]) {
                isFlag = 0;
                break;
            }
        }
        // If not flag, copy to original data
        if (!isFlag) {
            originalData[originalIndex++] = framedData[i];
        } else {
            i += 7; // Skip the flag sequence
        }
    }
    originalData[originalIndex] = '\0'; // Null-terminate the string
    printf("Original Data: %s\n", originalData);
}

int main() {
    char inputData[MAX_DATA_LENGTH];
    char framedData[MAX_DATA_LENGTH * 2]; // Assuming framing may double the size

    printf("Enter Data: ");
    scanf("%s", inputData); // Read input safely

    int inputLength = strlen(inputData);
    int framedIndex = 0;

    // Add flag at the beginning
    memcpy(framedData, flag, 8);
    framedIndex += 8;

    // Copy input data with flag handling
    for (int i = 0; i < inputLength; i++) {
        // Check for flag or escape sequences
        int isFlagOrEsc = 0;
        for (int j = 0; j < 8; j++) {
            if (inputData[i] == flag[j] || inputData[i] == esc[j]) {
                isFlagOrEsc = 1;
                break;
            }
        }
        // If flag or escape, add escape sequence
        if (isFlagOrEsc) {
            memcpy(framedData + framedIndex, esc, 8);
            framedIndex += 8;
        }
        framedData[framedIndex++] = inputData[i];
    }

    // Add flag at the end
    memcpy(framedData + framedIndex, flag, 8);
    framedIndex += 8;
    framedData[framedIndex] = '\0'; // Null-terminate the string

    printf("Framed Data: %s\n", framedData);

    // Simulate receiving end
    receiver(framedData);

    return 0;
}


/*
Enter Data: hello
Framed Data: 01111110hello01111110
Original Data: hello
*/
