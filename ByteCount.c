#include <stdio.h>
#define S 20

int data2[S];

void sender()
{
    int data1[S];
    int data;
    int data_len = 0, i = 0;
    int last_digit;
    
    printf("Enter Data:");
    scanf("%d", &data);

    // Extract digits from input and store in reverse order
    while (data != 0)
    {
        last_digit = data % 10;
        data = data / 10;
        data1[i++] = last_digit;
        data_len++;
    }

    // Store byte count as the first element in data2
    data2[0] = data_len;
    
    // Store data in data2 in Little-Endian format
    int k = 1;
    for (int i = data_len - 1; i >= 0; i--)
    {
        data2[k++] = data1[i];
    }

    printf("Sender's Data with byte count: ");
    for (int i = 0; i < data_len + 1; i++)
    {
        printf("%d", data2[i]);
    }
    printf("\n");
}

void receiver(int data[])
{
    int data_sz = data[0];
    
    printf("Original Received Data: ");
    for (int i = 1; i < data_sz + 1; i++)
    {
        printf("%d", data[i]);
    }
    printf("\n");
}

int main()
{
    sender();
    receiver(data2);
    return 0;
}


/*
Enter Data: 12345

Output:

Sender's Data with byte count: 512345
Original Received Data: 12345

*/

