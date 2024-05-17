#include<stdio.h>
#include<string.h>
int main(){
	char inpt[400];
	char barkercode[12] = "10110111000";
	char barkercodeNot[12]="01001000111";
	char otpt[4400]="\0";
	int temp1,err;
	printf("\nEnter Binary String / Data.\n");
	fgets(inpt, 400, stdin);
	for(int i=0;inpt[i]!='\0';i++){	

		if(inpt[i]=='1'){
			strcat(otpt, barkercode);
		}else if(inpt[i]=='0'){
			strcat(otpt, barkercodeNot);
		}
	strcat(otpt," ");
	}

	printf("\nThe given data converted to Barker Code is as follows.\n"); // this is the data that will be transmitted.
	printf("%s",otpt);
	printf("\n \nThe code again converted to data is as follows.\n");

	for(int i=0;otpt[i]!='\0';){
		err=0;
		
		if(otpt[i]==barkercode[0]){
			temp1=1;
		}
		else if(otpt[i]==barkercodeNot[0]){
			temp1=0;
		}
		else{
			err=1;
			break;
		}
		int k=i;
        i++;
		for(int j=1;j<11;j++){
			if(otpt[k+j]==barkercode[j] && temp1==1){
				temp1=1;
				i++;
				continue;
			}
			else if(otpt[k+j]==barkercodeNot[j] && temp1==0){
				temp1=0;
				i++;
				continue;
			}else{
                err=1;
                if(otpt[i]!='\0')
                    printf("\n\nData Transmission Error.\n");
				break; // breaking in both cases. even if it's transmission error, or if it has reached \0.
			}
		}
		if(err){
			break;
		}else{
			i+=1;
		}

		if(temp1){
			printf("1");
		}else if(!temp1){
			printf("0");
		}

	}	
    printf("\n");
}