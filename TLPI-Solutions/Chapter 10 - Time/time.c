#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>

void errExit(char* str){
	printf("Error in %s :\n",str);
	int errvar = errno;
	printf("%s\n",strerror(errvar));
	exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]){
	struct tm* t = gmtime();
	printf("Second : %d\n",t->tm_sec);
	exit(EXIT_SUCCESS);
}