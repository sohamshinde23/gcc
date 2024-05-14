#include <stdio.h>
#include <string.h>

#define S 100
#define FLAG_LENGTH 8
#define ESC_LENGTH 8

char flag[] = {'0', '1', '1', '1', '1', '1', '1', '0'};
char esc[] = {'0', '0', '0', '1', '1', '0', '1', '1'};

void receiver(char data[]);
void prependAppendFlag(char data[], char finalData[]);
void insertEscapes(char data[], char dataWithEscapes[]);

int main() {
    char data[S];
    char dataWithEscapes[S];
    char finalData[S];

    printf("Enter Data: ");
    scanf("%s", data);

    insertEscapes(data, dataWithEscapes);

    prependAppendFlag(dataWithEscapes, finalData);
    printf("Final data to be sent: %s\n", finalData);

    receiver(finalData);

    return 0;
}

void receiver(char data[]) {
    char res[S];
    int j = FLAG_LENGTH, p = 0;
    while (data[j] != '\0') {
        for (int i = 0; i < FLAG_LENGTH; i++) {
            res[p++] = data[j++];
        }
        j += ESC_LENGTH;
    }
    res[p - FLAG_LENGTH * 2] = '\0'; // Removing the extra flag at the end
    printf("Original Data is %s\n", res);
}

void prependAppendFlag(char data[], char finalData[]) {
    int len = strlen(data);
    for (int i = 0; i < FLAG_LENGTH; i++) {
        finalData[i] = flag[i];
    }
    for (int i = 0; i < len; i++) {
        finalData[FLAG_LENGTH + i] = data[i];
    }
    for (int i = 0; i < FLAG_LENGTH; i++) {
        finalData[FLAG_LENGTH + len + i] = flag[i];
    }
    finalData[2 * FLAG_LENGTH + len] = '\0';
}

void insertEscapes(char data[], char dataWithEscapes[]) {
    int j = 0, k = 0;
    while (data[j] != '\0') {
        int isFlag = 1;
        for (int i = 0; i < FLAG_LENGTH; i++) {
            if (data[j + i] != flag[i]) {
                isFlag = 0;
                break;
            }
        }
        if (isFlag) {
            for (int i = 0; i < ESC_LENGTH; i++) {
                dataWithEscapes[k++] = esc[i];
            }
        }
        for (int l = 0; l < FLAG_LENGTH; l++) {
            dataWithEscapes[k++] = data[j++];
        }
    }
    dataWithEscapes[k] = '\0';
}

/*
Enter Data: 01011010
Final data to be sent: 011111100101101001111110
Original Data is 01011010
*/
