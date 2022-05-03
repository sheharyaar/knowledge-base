#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>

void errExit(char *str)
{
	int errvar = errno;
	printf("Error in %s:\n",str);
	printf("%s\n",strerror(errno));
	errno = errvar;
	exit(EXIT_FAILURE);
}

int main(int argc, char* argv[])
{	
	if(argc<3 || strcmp(argv[1],"--help")==0){
		printf("Usage: %s filepath linkpath\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	char *filepath,*linkpath;
	filepath = argv[1];
	linkpath = argv[2];
	if(symlink(filepath,linkpath)==-1)
		errExit("symlink");

	exit(EXIT_SUCCESS);
}
