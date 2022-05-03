/*
	O_APPEND doesn't care about seek and just appends the data to the file.
*/
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

void errExit(char *str){
	printf("Error in %s",str);
	int errvar = errno;
	printf("%s\n",strerror(errvar));
	exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]){
	int fd;
	ssize_t bytesWrite;
	if(argc!=2){
		printf("Usage : %s filename\n",argv[0]);
		exit(EXIT_FAILURE);
	}

	fd = open(argv[1],O_RDWR | O_APPEND);
	if(fd == -1)
		errExit("open-fd");

	if(lseek(fd,0,SEEK_SET) == -1){
		errExit("seek");
	}

	bytesWrite = write(fd,"test",4);
	if(bytesWrite == -1)
		errExit("write-fd");
	
	if(close(fd) == -1){
		errExit("close-fd");
	}
	
	exit(EXIT_SUCCESS);
}		