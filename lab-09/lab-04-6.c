#include<stdio.h>
#include<math.h>

int file_size(char const* filename);

void Stat(char str[], int len){
	int i=0;
	while ((int)str[i]!=0 && (int)str[i]!=10){
		for(int j=0; j<26; j++){
			if ((int)str[i]==65+j || (int)str[i]==97+j){Counts[j]=Counts[j]+1; Total++;}
			//printf("i=%d, j=%d\n",i,j);			
		}
		i++;
	}
	return;
}

int main(){
printf("R12019/20, a term ended abruptly.\n");
}
