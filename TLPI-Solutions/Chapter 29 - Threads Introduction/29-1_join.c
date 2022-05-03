/*
	The program returns the value of : 35 which means EDEADLK
	This means there is dead locks and gets blockedd.
*/

#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

void errExit(char *s)
{	
	int errvar = errno;
	printf("Error in : %s with errno : %d\n",s,errno);
	printf("%s\n",strerror(errno));
	errno = errvar;
	exit(EXIT_FAILURE);
}

static void * threadFunc(void *arg)
{	
	char *s = (char *) arg;
	printf("%s",s);
	return (void *) strlen(s);
}

int main(int argc, char* argv[])
{	
	int s;
	s = pthread_join(pthread_self(),NULL);
	printf("S : %d\n",s);
	if(s!=0)
		errExit("pthread_join");

	exit(EXIT_SUCCESS);
}
