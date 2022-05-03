#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>

void errExit(char* str){
	int errvar = errno;
	printf("Error in %s. \n",str);
	printf("%s\n",strerror(errvar));
	exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]){
	char **paths;
	paths = (char **)malloc((argc-1)*sizeof(char *));
	if(argc<2){
		printf("Usage : %s file [anotherFIle] ... \n",argv[0]);
		exit(EXIT_FAILURE);
	}
	for(int i=1;i<argc;i++){
		paths[i-1] = argv[i];
	}
	for(int i=1;i<argc;i++){
		if(unlink(paths[i-1])== -1)
			errExit("unlink");
	}
	exit(EXIT_SUCCESS);
}
