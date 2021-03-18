#include<stdio.h>
#include<math.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<string.h>

int file_size(char const* filename){
	struct stat statbuf;
	int ret;
	ret = stat(filename,&statbuf);
	if (ret!=0) return -1;
	return statbuf.st_size;
}

int str2num(char str[], int strlen){
	int digit=1;
	int sum=0;
	for (int i=1; i<=strlen; i++){
		sum=sum+digit*(str[strlen-i]-'0');
		digit=digit*10;	
	}
	return sum;
}

int main(int argc, char* argv[]){
	size_t bufLen =8192;
	if (argc<3){
		if(argc==1){
			printf("Usage: %s source destination [destination]\n",argv[0]);
			return 0;
		}
		if(argc==2){
			printf("Usage: %s source destination [destination]\n",argv[0]);
			return 0;
		}
	}
    else{
	FILE *hFile1 = fopen(argv[1],"r");
	FILE *hFile2 = fopen(argv[2], "w+");
	
	//printf("str2num result is: %d\n", str2num(argv[3],strlen(argv[3])));
	//printf("argv[3]=%s\n",argv[3]);

	if (argv[3]!=NULL){
		int res=str2num(argv[3],strlen(argv[3]));
		if(res>0) bufLen=res;
		if (res==0) bufLen=file_size(argv[1]);
	}

	void *buffer = malloc(bufLen);

	if (!hFile1){
		perror("Failed to open file, reason: ");
		return 0;
	}
	printf("Copying from %s to %s with buffer size %lu bytes ... %d bytes copied successfully.\n",argv[1],argv[2],bufLen,file_size(argv[1]));
	while(1){
		size_t numRead = fread(buffer, 1, bufLen, hFile1);
		if (numRead <=0){
			if (feof(hFile1)<=0){
				//printf("Here1\n");		 
				break;
			}
			//perror("Failed to fread file, reason: ");
			fclose(hFile1);
			fclose(hFile2);
			//printf("Here3\n");
			return 0;
		}
		fwrite(buffer, 1 , numRead, hFile2);
	}
	fclose(hFile1);
	fclose(hFile2);
	//printf("Here2\n");
    }
	
	return 0;
}
