#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main() {

    char kbit[8][2][4]={
        {{"000\0"},{"200\0"}}, 
        {{"001\0"},{"300\0"}},
        {{"010\0"},{"400\0"}},
        {{"011\0"},{"500\0"}},
        {{"100\0"},{"600\0"}},
        {{"101\0"},{"700\0"}},
        {{"110\0"},{"800\0"}},
        {{"111\0"},{"900\0"}},
    };// kbit array -- first element is kbit number, 
    //here 3 bit number rather, and 2nd number is frequency in hz /mhz/ghz . you can give anything. 
    // \0 is to end string , and hence for a kbit number, the char array is of k+1, here i.e. 4.

    char drawArr[50][4];
    int drawArrIndex=0;

    char inpt[150]; 
    char inptTemp[4];
    
    int  inptsliced;
    int  iTemp;
    printf("Enter Binary Data\n");
    fgets(inpt,150,stdin);
    printf("--------------------------------------------------------------------------------");
    printf("\n\n");
    for(int i=0;inpt[i]!='\0';i=i+3){
        strncpy(inptTemp,inpt+i,3); // strncpy(destination_string,input_string+startingPos,len);
            for(int l=0;l<8;l++){
                if(inptTemp[0]==kbit[l][0][0] && inptTemp[1]==kbit[l][0][1] && inptTemp[2]==kbit[l][0][2]){
                    drawArr[drawArrIndex][0]=kbit[l][1][0];
                    drawArr[drawArrIndex][1]=kbit[l][1][1];
                    drawArr[drawArrIndex][2]=kbit[l][1][2];
                    drawArr[drawArrIndex++][3]=kbit[l][1][3];
                }
            }
            iTemp=i;
    }
    printf("\tTime\n\n");
    for(int i=0; i<drawArrIndex;i++){
        printf("\tt=%d \t",i);
        switch(atoi(drawArr[i])){
            case 200:   
                        break;
            case 300:   
                        printf("\t");
                        break;
            case 400:   
                        printf("\t\t");
                        break;
            case 500:   
                        printf("\t\t\t");            
                        break;
            case 600:   
                        printf("\t\t\t\t");  
                        break;
            case 700:   
                        printf("\t\t\t\t\t");  
                        break;
            case 800:
                        printf("\t\t\t\t\t\t");     
                        break;
            case 900:
                        printf("\t\t\t\t\t\t\t");     
                        break;
            default: exit(0);break;
        }
        printf(" -\n\n");
    }
        printf("--------------------------------------------------------------------------------\n");
        printf("\tFreq");
        printf("\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t",kbit[0][1],kbit[1][1],kbit[2][1],kbit[3][1],kbit[4][1],kbit[5][1],kbit[6][1],kbit[7][1]);
        printf("\n\t(Hz)\n");
    return 0;
}