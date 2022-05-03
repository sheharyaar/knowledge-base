#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <sys/utsname.h>
#include <stdlib.h>

void errExit(char* str){
	int errvar;
	errvar = errno;
	printf("Error in : %s\n",str);
	printf("%s\n",strerror(errvar));
	exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]){
	struct utsname uts;
	if(uname(&uts) == -1)
		errExit("uname");

	printf("Node name: %s\n",uts.nodename);
	printf("System name: %s\n",uts.sysname);
	printf("Release: %s\n",uts.release);
	printf("Version: %s\n",uts.version);
	printf("Machine: %s\n",uts.machine);

#ifdef _GNU_SOURCE
	printf("Domain name: %s\n",uts.domainname);
#endif

	exit(EXIT_SUCCESS);
}