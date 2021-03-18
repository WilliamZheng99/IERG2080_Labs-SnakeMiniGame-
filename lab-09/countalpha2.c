#include<stdio.h>
#include<math.h>
#include<sys/stat.h>

int Counts[26]={0};
double Percentage[26]={0};
int Total=0;

int file_size(char const* filename){
	struct stat statbuf;
	int ret;
	ret = stat(filename,&statbuf);
	if (ret!=0) return -1;
	return statbuf.st_size;
}

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

int main(int argc, char *argv[]){
	size_t const bufLen = 100;
	char lineBuf[bufLen];
	if (argc <2) {// No file.
		printf("Usage : %s filename\n", argv[0]);
		return 0;
	}

	//printf("argc=%d\n",argc);
	int l=1;
   while(l<4){
	FILE *hFile = fopen(argv[l],"r");
	if (!hFile) {
		perror("Failed to open file, reason: ");
		return 0;
	}
	while(1){
		if(!fgets(lineBuf, bufLen, hFile)){
			//printf("Here1\n");
			if(feof(hFile)) break;
			perror("Failed to open file, reason: ");
			fclose(hFile);
			return 0;
		}
		//fputs(lineBuf, stdout);
		Stat(lineBuf,bufLen);
		lineBuf[bufLen-1]=0; //The terminus.
	}
	fclose(hFile);
	printf("Processing %s ...%d bytes processed successfully.\n",argv[l], file_size(argv[l]) );
	l=l+1;
   }
	printf("Letter  Counts    Percentage\n");
	for (int k=0; k<26; k++){
		Percentage[k]=(double)Counts[k]/(double)Total*100; 
		printf("%c        %d        %.2f%% \n",(char)(65+k), Counts[k], Percentage[k]);	
	}
	//printf("[%s]\n", argv[4]);

	return 0;
}
