#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>

void errExit(char *str)
{
	int errvar = errno;
	printf("Error in %s:\n",str);
	printf("%s\n",strerror(errno));
	errno = errvar;
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
	if(argc<2 || strcmp(argv[1],"--help")==0){
		printf("Usage: %s pathname\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	char *pathname = argv[1];
	if(remove(pathname)==-1)
		errExit("rmdir");
	exit(EXIT_SUCCESS);
}
