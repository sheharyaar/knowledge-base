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
	int fd1,fd2,fd3;
	char *file = "myfile";
	fd1 = open(file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR );
	fd2 = dup(fd1);
	fd3 = open(file, O_RDWR);

	write(fd1,"Hello,",6); // Hello,
	write(fd2,"world",6);	// Hello,world
	lseek(fd2,0,SEEK_SET);
	write(fd1,"HELLO,",6);	// HELLO,world
	write(fd3,"Gidday",6);	//Giddayworld

	close(fd1);
	close(fd3);
	exit(EXIT_SUCCESS);
}