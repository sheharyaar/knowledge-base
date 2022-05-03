/*
	The file with x parameter will be less in size as the file offset is overwritten by
	the different process due to race condition.

	The file with O_APPEND will be correct in size as it always appends the data and
	doesn't care about race conditions.
*/
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

void errExit(char* str){
	printf("Error in %s :\n",str);
	int errvar = errno;
	printf("%s\n",strerror(errvar));
	exit(EXIT_FAILURE); 
}

int main(int argc, char* argv[]){
	int fd;
	int flag;
	ssize_t bytesWritten;

	if(argc<2){
		printf("Usage : %s filename num-bytes [x]\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	
	flag = O_RDWR | O_CREAT;
	if(argc != 4){
		flag |= O_APPEND;
	}

	fd = open(argv[1],flag,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if(fd== -1)
		errExit("open-fd");

	long long int count = atoll(argv[2]);
	while(count--){
		if(argc == 4){
			if(lseek(fd,0,SEEK_END) == -1){
				errExit("lseek");

			}
		}
		bytesWritten = write(fd,"0",1);
		if(bytesWritten == -1)
			errExit("write-fd");
	}

	if(close(fd) == -1){
		errExit("close-fd");
	}
	
	exit(EXIT_SUCCESS);
}						