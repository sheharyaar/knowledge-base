/* 
	Implement getopt()
	Implement /dev/tty for better use till EOF
*/
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <stdlib.h>

void errExit(char* str){
		int errvar = errno;
		printf("Error in %s :\n",str);
		printf("%s\n",strerror(errvar));
}

int main(int argc, char* argv[]){
	int fd;
	char* file;
	if(argc < 2){
		printf("Usage: %s [-a] file\n",argv[0]);
		return 1;
	}
	if(argc==2){
		file = argv[1];
		fd = open(file,
			O_RDWR | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);	
	}
	if(argc==3){
		file = argv[2];
		fd = open(file,
			O_RDWR | O_CREAT | O_APPEND ,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);	
	}
	if(fd==-1){
		errExit("open");
		return 1;
	}

	ssize_t red;
	ssize_t writen;

	int tty;
	tty = open("/dev/tty",O_RDWR);
	char c;
	int count =0;
	while(red){
		red = read(tty,&c,1);
		if(red== -1){
			errExit("read-tty");
			return 1;
		}
		if(c!=EOF){
			writen = write(fd,&c,1);
			if(writen==-1){
				errExit("write");
				return 1;
			}
			count++;
		}
	}
	if(close(fd)== -1){
		errExit("close-fd");
		return 1;
	}

	if(close(tty)== -1){
		errExit("close-tty");
		return 1;
	}

	return 0;
}