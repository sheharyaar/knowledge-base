#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void errExit(int err, char *str)
{
	printf("Error in : %s\n",str);
	if(err == -1)
		printf("%s\n",strerror(errno));
	else
		printf("%s\n",strerror(err));

	fflush(stdout);
	exit(EXIT_FAILURE);
}

static void* threadFunc(void *arg)
{	
	sigset_t blockMask,emptyMask,pendingSet;
	sigfillset(&blockMask);
	sigemptyset(&emptyMask);

	int threadArg,s,sig;
	threadArg = *(int *)arg;

	s = pthread_sigmask(SIG_SETMASK,&blockMask,NULL);
	if(s!=0)
		errExit(s,"pthread_sigmask");

	sleep(5);	

	if(sigpending(&pendingSet) == -1)
		errExit(-1,"sigpending");
	
	for(sig = 1; sig < NSIG ; sig++){
		if(sigismember(&pendingSet,sig)){
			printf("Thread %03d SIGNAL %02d\n",threadArg,sig);
			}
	}

	s = pthread_sigmask(SIG_SETMASK,&emptyMask,NULL);
	if(s!=0)
		errExit(s,"pthread_sigmask");
	
	return NULL;
}

int main(int argc, char *argv[])
{
	// Creating empty mask from process
	sigset_t procMask;
	sigemptyset(&procMask);

	pthread_t t1,t2;
	int s,arg1,arg2;
	
	arg1 = 1;
	s = pthread_create(&t1,NULL,threadFunc,&arg1);
	if(s!=0)
		errExit(s,"pthread_create");
	
	arg2 = 2;
	s = pthread_create(&t2,NULL,threadFunc,&arg2);
	if(s!=0)
		errExit(s,"pthread_create");	
	
	sleep(2);
	pthread_kill(t1,SIGINT);
	pthread_kill(t2,SIGFPE);

	s = pthread_join(t1,NULL);
	if(s!=0)
		errExit(s,"pthread_join");

	s = pthread_join(t2,NULL);
	if(s!=0)
		errExit(s,"pthread_join");

	exit(EXIT_SUCCESS);
}
