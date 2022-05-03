#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>

void errExit(char *str)
{
	int errvar = errno;
	printf("Error in %s:\n",str);
	printf("%s\n",strerror(errno));
	errno = errvar;
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{	
	if(argc<2 || strcmp(argv[1],"--help")==0){
		printf("Usage: %s dirpath\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	char *dirpath = argv[1];
	DIR *dirp;
	struct dirent *dp;

	// Opening directory
	dirp = opendir(dirpath);
	if(dirp == NULL)
		errExit("open-dir");
	
	// Reading directory
	dp = readdir(dirp);
	for(;;){
		errno = 0;
		dp = readdir(dirp);
		if(dp == NULL)
			break;

		if(strcmp(dp->d_name,".") == 0 || strcmp(dp->d_name,"..")==0)
			continue;

		printf("%ld %s\n",dp->d_ino,dp->d_name);
	}
	
	if(errno!=0)
		errExit("read-dir");

	if(closedir(dirp)==-1)
		errExit("close-dir");

	exit(EXIT_SUCCESS);
}
