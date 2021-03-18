#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>


int main(){
	size_t buffsize=1024;
	char *buffer;
	while(1){
		buffer=malloc(buffsize);
		//printf("DMA: current buffsize is %ld\n", buffsize);
		//fflush(stdout);
		if (!buffer){
			printf("Allocating heap memory block of size %ld ... failed!\n", buffsize);
			printf("Maximum heap allocation is %ld bytes\n", buffsize/2);
			free(buffer);
			break;
		}
		else{
			//printf("[%p]\n",buffer);
			free(buffer);
			buffsize=2*buffsize;
		}
	}
	//Above is okay
	
	size_t Vsize=1024;//We know this will lead to core dumped.
	int i=1;
	int Largest_size=0;
	while(1){
		//printf("i=%d.",i);
		char bufferV[Vsize];
		printf("VLA: Num_iter is %d, current buffsize is=%ld\n",i, Vsize);
		fflush(stdout);
		Largest_size=Largest_size+Vsize;
		Vsize=Vsize*2;
		printf("Largest size is %d\n", Largest_size);
		i=i+1;
		//printf("1");
	}
	

	/*
	size_t Vsize=8374720;
	int i=1;
	while(1){
		char bufferV[Vsize];
		Vsize=Vsize+1;
		printf("addr is: %p.\n",&bufferV[0]);
		printf("Size is: %ld\n",Vsize);
	}
	*/
	
	
return 0;
}
