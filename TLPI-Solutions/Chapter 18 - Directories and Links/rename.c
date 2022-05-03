#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>

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
	if(argc < 3 || strcmp(argv[1],"--help")==0){
		printf("Usage: %s oldpath newpath\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	char *oldpath, *newpath;
	oldpath = argv[1];
	newpath = argv[2];
	if(rename(oldpath,newpath)==-1)
		errExit("rename");
	exit(EXIT_SUCCESS);
}
