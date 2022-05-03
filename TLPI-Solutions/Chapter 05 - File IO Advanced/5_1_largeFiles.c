#define _FILE_OFFSET_BITS 64
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

void errExit(char *str){
	printf("Error in %s :\n",str);
	int errvar = errno;
	printf("%s\n",strerror(errvar));
	exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]){
	int fd;
	off_t off;

	if(argc<3){
		printf("USage : %s pathname offset\n",argv[0]);
		exit(EXIT_FAILURE);
	}

	fd = open(argv[1],
		O_CREAT | O_RDWR | O_TRUNC,
		S_IRUSR | S_IWUSR);
	
	if(fd == -1)
		errExit("open-fd");

	off = atoll(argv[2]);
	if(lseek(fd,off,SEEK_SET) == -1){
		errExit("lseek");
	}

	if(write(fd,"abcd",4)==-1){
		errExit("write-fd");
	}

	if(close(fd) == -1){
		errExit("close-fd");
	}
	
	exit(EXIT_SUCCESS);
}