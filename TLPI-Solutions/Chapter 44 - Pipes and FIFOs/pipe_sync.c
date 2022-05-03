#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

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
	if(argc<2 || strcmp(argv[1],"--help")==0){
		printf("Usage : %s [time1] [time2] ...\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	
	setbuf(stdout,NULL);

	int pfd[2];
	int j,dummy;
	time_t t;

	if(pipe(pfd)==-1)
		errExit("pipe");

	// Print Time
	time(&t);
	printf("%s : Parent ready to fork\n",ctime(&t));

	for(j=1;j<argc;j++){
		switch(fork()){
			case -1: 
				errExit("fork()");

			case 0 :
				if(close(pfd[0])==-1)
						errExit("close - child");
				
				sleep(atol(argv[j]));
				// Print time
				time(&t);
				printf("%s : Child %d completed.\n",ctime(&t),j);

				if(close(pfd[1]) == -1)
					errExit("close-child");

				_exit(EXIT_SUCCESS);

			default :
				break;
		}
	}


	if(close(pfd[1])==-1)
		errExit("close");

	if(read(pfd[0],&dummy,1) !=0 )
		errExit("parent didnt get EOF");
	
	//Print Time
	time(&t);
	printf("%s : Parent ready to go\n",ctime(&t));

	if(close(pfd[0]) == -1)
			errExit("close");

	exit(EXIT_SUCCESS);
}
