#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

#define BUF_SIZE 10

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
	if(argc != 2 || strcmp(argv[1],"--help") == 0){
		printf("Usage : %s [string]\n",argv[0]);
		exit(EXIT_SUCCESS);
	}
	
	int pfd[2];
	char buf[BUF_SIZE];
	ssize_t numRead;
	
	if(pipe(pfd)==-1)
		errExit("pipe");

	switch(fork()){

		case -1 : 
			errExit("fork");

		case 0 :{
			if(close(pfd[1])==-1)
				errExit("close fd");

			for(;;){
				numRead = read(pfd[0],buf,BUF_SIZE);
				if(numRead == -1)
					errExit("read");

				if(numRead == 0)
					break;

				if(write(STDOUT_FILENO,buf,numRead) != numRead)
					errExit("child - partial/failed write");			
			}

			write(STDOUT_FILENO, "\n", 1);
			if(close(pfd[0]) == -1)
				errExit("close");
			
			_exit(EXIT_SUCCESS);

		}
		
		default : {
			if(close(pfd[0]) == -1)
				errExit("close - parent");

			if(write(pfd[1],argv[1],strlen(argv[1])) != strlen(argv[1]))
				errExit("parent - failed/partial write");

			if(close(pfd[1])==-1)
				errExit("close");

			wait(NULL);
			exit(EXIT_SUCCESS);
		}

	}

}
