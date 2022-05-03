#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/stat.h>

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
		printf("Usage: %s dirName\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	char *pathname = argv[1];
	mode_t mode = S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH;
	if(mkdir(pathname,mode)==-1)
		errExit("mkdir");
	exit(EXIT_SUCCESS);
}

