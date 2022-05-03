/* 
	Program to perform function similar to cp even for files with holes.
*/
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

// Error handling function
void errExit(char *str){
	printf("Error in %s :\n",str);
	int errvar = errno;
	printf("%s\n",strerror(errvar));
	exit(1);
}

int main(int argc, char * argv[]){
	int source,target;
	ssize_t bytes_read=1, bytes_write;
	char ch;

	// Handling command line
	if(argc<3){
		printf("Usage : %s source destination\n",argv[0]);
		exit(1);
	}
	
	// Opening source
	source = open(argv[1],O_RDONLY);
	if(source == -1){
		errExit("opening source");
	}
	
	// Opening target
	target = open(argv[2],
		O_RDWR | O_TRUNC | O_CREAT,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH 
		);
	if(target == -1){
		errExit("opening target");
	}

	// Reading from source and writing to target
	while((bytes_read = read(source,&ch,1))>0){
		if(bytes_read == -1){
			errExit("reading source");
		}
		if(ch!=EOF){
			bytes_write = write(target,&ch,1);
			if(bytes_write == -1){
				errExit("writing target");
			}
		}
	}

	// Closing the files
	if(close(source) == -1){
		errExit("closing source");
	}
	if(close(target) == -1){
		errExit("closing target");
	}

	return 0;
}