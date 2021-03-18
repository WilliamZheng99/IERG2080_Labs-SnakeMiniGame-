#include<stdio.h>

int file_size(char const* filename){
	struct stat statbuf;
	int ret;
	ret = stat(filename,&statbuf);
	if (ret!=0) return -1;
	return statbuf.st_size;
}


int main(){
printf("LAB\n");
}
