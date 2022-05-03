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
	ssize_t written;
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
		printf("Enter the data of size %d : ",size);
		scanf("%s",ptr[i]); // should be changed to prevent buffer overflow
	}

	fd = open("myfile-write",O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
	if(fd == -1)
		errExit("open-fd");

	for(int i=0;i<buffers;i++){
		written = write(fd,iov[i].iov_base,iov[i].iov_len);
		if(written == -1)
			errExit("write-fd");
	}

	for(int i=0;i<buffers;i++){
		free(ptr[i]);
	}

	if(close(fd == -1))
		errExit("close-fd");

	exit(EXIT_SUCCESS);
}