#include <stdio.h>
#include <pthread.h>
#include <sys/wait.h>
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

static void * threadFunc(void *arg)
{
	pid_t childPid;
	int thrarg;
	thrarg = *(int *)arg;
	
	switch(childPid = fork()){
		case -1 :
			errExit(-1,"fork");

		case 0 :{
			printf("[ Thread %03d ] Child created with PID : %d\n",thrarg,getpid());
			_exit(EXIT_SUCCESS);
		}

		default :{
			while((childPid = wait(NULL)) != -1)
				continue;
			if(errno!=ECHILD)
				errExit(-1,"wait");

			printf("[ Thread %03d ] Child exited with PID : %d\n",thrarg,childPid);
		 }
	}

	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t t1,t2,t3;
	int s,arg1,arg2,arg3;

	arg1 = 1;
	s = pthread_create(&t1,NULL,threadFunc,&arg1);
	if(s!=0)
		errExit(s,"pthread_create");
	
	arg2 = 2;
	s = pthread_create(&t2,NULL,threadFunc,&arg2);
	if(s!=0)
		errExit(s,"pthread_create");
	
	arg3 = 3;
	s = pthread_create(&t3,NULL,threadFunc,&arg3);
	if(s!=0)
		errExit(s,"pthread_create");


	s = pthread_join(t1,NULL);
	if(s!=0)
		errExit(s,"pthread_join");

	s = pthread_join(t2,NULL);
	if(s!=0)
		errExit(s,"pthread_join");

	s = pthread_join(t3,NULL);
	if(s!=0)
		errExit(s,"pthread_join");
	
	exit(EXIT_SUCCESS);
}
