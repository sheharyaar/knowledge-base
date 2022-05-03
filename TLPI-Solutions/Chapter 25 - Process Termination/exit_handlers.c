#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

void atexit1(void)
{
	printf("atexit 1 called!\n");
}

void atexit2(void)
{
	printf("atexit 2 called!\n");
}

void atexit3(void)
{
	printf("atexit 3 called!\n");
}

int main(int argc, char *argv[])
{	
	atexit(atexit1);
	atexit(atexit2);
	atexit(atexit3);
	exit(2);
}
