#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>

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
	if(argc < 2 || strcmp(argv[1],"--help") == 0){
		printf("Program to read the contents of a symbolic link\nUsage: %s symlinkPath\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	char *pathname = argv[1];
	char *buffer = malloc(255*sizeof(char));
	size_t buf_size = 255;
	ssize_t written;
	written = readlink(pathname,buffer,buf_size);
	if(written == -1)
		errExit("readlink");
	printf("The contents of the buffer are : \n");
	printf("%s\n",buffer);
	exit(EXIT_SUCCESS);
}
