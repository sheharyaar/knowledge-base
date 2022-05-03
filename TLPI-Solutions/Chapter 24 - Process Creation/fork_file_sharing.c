#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

void errExit(char *str)
{
	int errvar = errno;
	printf("Error in : %s\n",str);
	printf("%s\n",strerror(errno));
	errno = errvar;
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{	
	int fd,flags;
	char template[] = "/tmp/testXXXXXX";
	
	setbuf(stdout,NULL);

	fd = mkstemp(template);
	if(fd == -1)
		errExit("mkstemp");
	
	printf("File offset before fork() : %lld\n",
		(long long) lseek(fd,0,SEEK_CUR));

	flags = fcntl(fd,F_GETFL);
	if(flags==-1)
		errExit("fcntl - F_GETFL()");
	printf("O_APPEND flag before fork() is : %s\n",
		(flags & O_APPEND)? "ON" : "OFF");
	
	switch(fork()){
	case -1 :
		errExit("fork");
	
	case 0 :
		if(lseek(fd,1000,SEEK_SET)==-1)
			errExit("lseek-child");

		flags = fcntl(fd,F_GETFL);
		if(flags == -1)
			errExit("F_GETFL child");

		flags |= O_APPEND;

		if(fcntl(fd,F_SETFL,flags)==-1)
			errExit("F_SETFL child");

		_exit(EXIT_SUCCESS);
			
	default :
		if(wait(NULL)==-1)
			errExit("wait");
		printf("Child has exited!\n");

		printf("File offset after fork() is : %lld\n",
			(long long) lseek(fd,0,SEEK_CUR));

		flags = fcntl(fd,F_GETFL);
		if(flags == -1)
		errExit("F_GETFL after fork");
		
		printf("O_APPEND flag after fork is : %s\n",
			(flags & O_APPEND)? "ON" : "OFF");	
		
		
		if(close(fd) == -1)
			errExit("close");
	
		exit(EXIT_SUCCESS);
	}
}
