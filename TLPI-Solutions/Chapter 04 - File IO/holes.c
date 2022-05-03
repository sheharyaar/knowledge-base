/*
	Program to create a file with hole
*/
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

void errExit(char *str){
	printf("Error in %s :\n",str);
	int errvar = errno;
	printf("%s\n",strerror(errvar));
	exit(1);
}

int main(int argc, char* argv[]){
	ssize_t bytes_write;
	char* buf = "Holefile";

	if(argc<2){
		printf("Usage : %s fileName\n",argv[0]);
		exit(1);
	}

	int fd = open(argv[1],
		O_RDWR | O_TRUNC | O_CREAT,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if(fd==-1){
		errExit("open-fd");
	}
	
	lseek(fd,1024,SEEK_SET);

	bytes_write = write(fd,buf,strlen(buf));
	if(bytes_write == -1){
		errExit("write-fd");
	}

	if(close(fd) == -1){
		errExit("close-fd");
	}
	return 0;
}