#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#define MAX_BUFFER 100

struct iovec{
	void *iov_base;
	size_t iov_len;		
};

void errExit(char *str){
	printf("Error in %s :\n",str);
	int errvar = errno;
	printf("%s\n",strerror(errvar));
	exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]){
	int size,buffers;
	int fd;
	ssize_t readData;
	void* ptr[MAX_BUFFER]; // array of pointers to void
	struct iovec iov[MAX_BUFFER];

	printf("Enter the number of buffers : ");
	scanf("%d",&buffers);
	for(int i=0;i<buffers;i++){
		printf("Enter the size of buffer %d : ",i+1);
		scanf("%d",&size);
		ptr[i] = (char *)malloc(size*sizeof(char));
		iov[i].iov_base = ptr[i];
		iov[i].iov_len = size*sizeof(char);
	}
	fd = open("myfile",O_RDONLY);
	if(fd == -1)
		errExit("open-fd");

	for(int i=0;i<buffers;i++){
		readData = read(fd,iov[i].iov_base,iov[i].iov_len);
		if(readData == -1)
			errExit("read-fd");
		printf("Data %d : %s\n",i,ptr[i]);
	}

	for(int i=0;i<buffers;i++){
		free(ptr[i]);
	}

	if(close(fd == -1))
		errExit("close-fd");

	exit(EXIT_SUCCESS);
}