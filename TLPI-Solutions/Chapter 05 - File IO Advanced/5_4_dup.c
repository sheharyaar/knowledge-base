#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

void errExit(char *str){
	printf("Error occurred at %s :\n",str);
	int errorvar = errno;
	printf("%s\n",strerror(errorvar));
	exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]){
	int fd;
	int dupfd;

	fd = open("myfile", O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR );
	if(fd == -1)
		errExit("open-fd");

	if(argc == 1){
		dupfd = fcntl(fd,F_DUPFD,0); 
		/*
			0 is necessary as without 0 F_DUPFD wont assign the
			 lowest available file descriptor.
		*/
		if(dupfd == -1){
			errExit("fcntl");
		}
		printf("New fd : %d\n",dupfd);
	}else{
		if(atoi(argv[1]) == fd){
			dupfd = fd;
		}else{
			// Closing the arg fd if already in use.
			if(fcntl(atoi(argv[1]),F_GETFL)>0){
				if(close(atoi(argv[1])) == -1)
					errExit("close-oldfd");
				printf("closed the existing fd\n");
			}
			dupfd = fcntl(fd,F_DUPFD,atoi(argv[1]));
			printf("New fd for pid %d : %d\n",getpid(),dupfd);
		}
	}

	if(close(fd) == -1)
		errExit("close-fd");

	if(dupfd != fd){
		if(close(dupfd) == -1)
			errExit("close-dupfd");
	}
	exit(EXIT_SUCCESS);
}