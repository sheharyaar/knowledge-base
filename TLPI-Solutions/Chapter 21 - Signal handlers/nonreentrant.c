#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <crypt.h>

void errExit(char *str)
{
	int errvar = errno;
	printf("Error in %s :\n",str);
	printf("%s\n",strerror(errno));
	errno = errvar;
	exit(EXIT_FAILURE);
}

static char *str2;
static int handled = 0;

static void handler(int sig)
{
	crypt(str2,"xx");
	handled++;
}

int main(int argc, char* argv[])
{	
	
	exit(EXIT_SUCCESS);
}	
