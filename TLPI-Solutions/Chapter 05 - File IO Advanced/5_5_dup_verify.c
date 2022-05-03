#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

void errExit(char *str){
	printf("Error in %s :\n",str);
	int errvar = errno;
	printf("%s\n",strerror(errvar));
	exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]){
	int oldfd,newfd;
	int oldFlags,newFlags;
	oldfd = open("myfile", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	if(oldfd == -1)
		errExit("open-oldfd");
	newfd = dup(oldfd);
	if(newfd == -1)
		errExit("dup");

	oldFlags = fcntl(oldfd,F_GETFL);
	if(oldFlags == -1)
		errExit("old GETFL");

	newFlags = fcntl(newfd,F_GETFL);
	if(newFlags == -1)
		errExit("new GETFL");
	
	printf("PID : %d\n",getpid());

	if(oldFlags == newFlags){
		printf("Yeah they share the same flags\n");
	}else{
		printf("No they do not share the same fags\n");
	}

	if(lseek(oldfd,10,SEEK_SET) == -1)
		errExit("lseek");
	printf("Seeked the old fd to 10 byte offset.\n");

	if(write(newfd,"Hello",5) == -1)
		errExit("write");	
	printf("Write Hello using the new fd.\n");

	lseek(oldfd,-5,SEEK_END);
	printf("Seek the old fd back by 5 bytes from the end\n");

	char buf[6];
	if(read(oldfd,buf,5) == -1)
		errExit("read");
	printf("Reading 5 bytes now\n");

	if(strcmp(buf,"Hello") == 0){
		printf("Yes they share the same file offset because the read "
			"data of old fd is the same as written data of new fd\n");
	}else{
		printf("No they do not share the same file offset\n");
	}

	if(close(oldfd == -1))
		errExit("close-oldfd");

	exit(EXIT_SUCCESS);
}