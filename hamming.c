#include <stdio.h>
#include <string.h>
#include <math.h>
#define N 50

char *fill_parity(char data[],int p);
char* error(char data[]);
void receive(char data[]);
void reverseString(char *str);

int main(){
    char data[N];
    int choice;
    printf("------------------------------------------------------------\n");
    do{
    printf("Enter Data: ");
    scanf("%s",data);
    data[strlen(data)] ='\0';
    reverseString(data);
    //To calculate number of parity bits
    int data_sz = strlen(data);
    int p=1;
    while(1){
        if(pow(2,p)>= data_sz+p+1){
            break;
        }
        p++;
    }
    printf("Required number of Parity Bits: %d\n",p);

    //new string array for storing data with parity bits 
    int j = 0, k=0, l=0;
    char data1 [N];
    for(j=0; j<data_sz+p; j++){

    if(j+1 == pow(2,k)){
        data1[j]= 'p'; //p->null value
        k++; 
    }else{
        data1[j] = data[l];
        l++;
    }
    }
    data1[data_sz+p]='\0';
    printf("Data with parity bits: %s\n",data1);
    printf("------------------------------------------------------------\n");

    fill_parity(data1,p); 
    printf("------------------------------------------------------------\n");

    printf("1.Enter [a] to pass data without error.\n2.Enter [b] to pass data with error.\n");
    char ch;
    scanf(" %c",&ch);

    switch(ch){
        case 'a': receive(data1);
        break;
        case 'b': error(data1); receive(data1);
        break;
        default:printf("Wrong Input.");
    }

    printf("\nDo you want to continue: [yes(1)/no(0)] ->");
    scanf("%d",&choice);
     if(choice == 0){
    printf("\n-----------------------Thank You!---------------------------\n\n");
    }else{
    printf("------------------------------------------------------------\n\n");
    }
    }while(choice==1);
    return 0;
}

char *fill_parity(char data1[],int p){
    //filling null parity positions
    char q[N];
    while(p>=1){
        int count = 0, a=0;
        int i = pow(2,p-1);
        int z = i;
        for(i=z-1; i<strlen(data1); i++){
            if(count == z){
                i=i+z-1;
                count = 0;
            }else{
            q[a] = data1[i];
            a++;
            count ++;
            }
        }
        q[a] = '\0';
        printf("For Parity at %dth: %s\n",z,q);
        count = 0;
        for(i=0; i<strlen(q); i++){
            if(q[i]=='1'){
                count++;
            }
        }
        if(count%2 == 0){
            data1[z-1] = '0';
        }
        else{
            data1[z-1] = '1';
        }
        printf("Data: %s\n",data1);
        p--;
    } 
    return data1;
}

char* error(char data[]){
    printf("------------------------------------------------------------\n");

    printf("Final data: ");
    for(int d=0; d<strlen(data); d++){
        printf("%c",data[d]);
    }
    printf("\n");

    printf("Enter position for switching a bit:");
    int pos;
    scanf("%d",&pos);
    if(data[pos-1]=='0'){
        data[pos-1]='1';
    }else{
        data[pos-1]='0';
    }
    printf("Data after fliping a bit: %s\n",data);
    printf("------------------------------------------------------------\n");
    return data;
}

void receive(char data[]){
    int i=0;
    char q[N];
    int arr[N];
    while(1){
    if(strlen(data) <= pow(2,i)){
        break;
    }
    i++;
    }
    int y = i;
    while(i!=0){
        int a=0, count=0;
        int s = pow(2,i-1);
        for(int j=s-1; j<strlen(data); j++){
            if(count == s){
                j=j+s-1;
                count = 0;
            }else{
            q[a] = data[j];
            a++;
            count ++;
            }
        }
        q[a] = '\0';
        printf("For Parity at %dth: %s\n",s,q);
        count=0;
        for(int k=1; k<strlen(q); k++){
            if(q[k]=='1'){
                count++;
            }
        }
        if(count%2==0 && q[0]=='0'){
            arr[i-1]=0;
        }else if(count%2!=0 && q[0]=='1'){
            arr[i-1]=0;
        }
        else{
            arr[i-1]=1;
        }

        i--;
    }
    int flag = 1 ;
    printf("Resultant Array:");
    for(int e=y-1; e>=0; e--){
        printf("%d",arr[e]);
        if(arr[e]==1){
            flag=0;
        }
    }
    printf("\n------------------------------------------------------------\n");
    if(flag==0){
        printf("!!! Data Rejected !!!\n");
    }else{
        printf("!!! Data Accepted !!!\n");
    }
    printf("------------------------------------------------------------\n");
}

void reverseString(char *str) {
    int length = strlen(str);
    int start = 0;
    int end = length - 1;

    while (start < end) {
        // Swap characters at the start and end indices
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;

        // Move indices towards the center
        start++;
        end--;
    }
}


// gcc hamming.c -lm -o h
// ./h
