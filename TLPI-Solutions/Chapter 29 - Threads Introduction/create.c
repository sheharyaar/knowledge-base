#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

static void * func(void *arg);

void errExit(char *str)
{
	int errvar = errno;
	printf("error in %s\n",str);
	printf("%s\n",strerror(errno));
	errno = errvar;
	exit(EXIT_FAILURE);
}

int main(int argc, char* argv[])
{
	pthread_t t1;
	void *res;
	int s;

	s = pthread_create(&t1,NULL,func,"Hello World\n");
	if(s!=0)
		errExit("pthread_create");

	printf("Message from main()\n");
	s = pthread_join(t1,&res);
	if(s!=0)
		errExit("pthread_join");

	printf("Thread terminated %ld\n",(long)res);

	exit(EXIT_SUCCESS);
}

static void * func(void *arg)
{
	char *s = (char *) arg;
	printf("%s",s);
	return (void *) strlen(s);
}

