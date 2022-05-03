#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

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
	int status = 3;
	switch(fork()){
	case -1 :
		errExit("fork");
	case 0 :
		printf("Child Exited!\n");
		exit(atoi(argv[1]));
	default :
		printf("%d\n",wait(&status));
		printf("Status received : %d\n",status);
	}
	exit(EXIT_SUCCESS);
}
