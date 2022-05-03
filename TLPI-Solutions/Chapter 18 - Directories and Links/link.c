#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

void errExit(char* str){
	int errvar = errno;
	printf("Error in %s\n",str);
	printf("%s\n",strerror(errvar));
	exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]){
	char *old,*new;
	if(argc<3){
		printf("Usage : %s oldfile newfile \n",argv[0]);
		exit(EXIT_FAILURE);
	}
	old = argv[1];
	new = argv[2];
	if(link(old,new) == -1)
		errExit("link");

	exit(EXIT_SUCCESS);
}
