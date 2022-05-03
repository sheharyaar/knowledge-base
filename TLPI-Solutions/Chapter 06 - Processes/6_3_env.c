/* 
	implementation of setenv() and unsetenv() using getenv() and 
	putenv(). setenv() takes in 3 arguments : name,value and overwrite.
*/
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

extern char** environ;

void errExit(char* str){
	printf("Error in %s :\n",str);
	int errvar = errno;
	printf("%s\n",strerror(errvar));
	exit(EXIT_FAILURE);
}

int setEnv(char* name,char* value,int overwrite){
	char *retEnv = getenv(name);
	if(retEnv == NULL || overwrite == 1){
		char str1[1000]="";
		strcat(str1,name);
		strcat(str1,"=");
		strcat(str1,value);
		char *str = str1;
		if(putenv(str) == 0){
			printf("Successfully added the environment variable.\n%s\n",str);
		}else{
			errExit("setenv");
		}
	}else{
		printf("Environ not added\n");
	}
	return 0;
}

int unsetEnv(char* name){
	char* retEnv = getenv(name);
	if(retEnv == NULL){
		printf("Entry not found");
		return -1;
	}else{
		int counter=0;
		while(getenv(name)!=NULL){
			char str1[1000]="";
			strcat(str1,name);
			strcat(str1,"=");
			strcat(str1,retEnv);
			putenv(str1);
			str1[0]='\0';
			counter++;
		}
		printf("\n\nSuccessfully deleted %d entries.\n\n",counter);
		return 0;
	}
}

int main(int argc, char* argv[]){

	char **ep;
	for(ep = environ; *ep!=NULL;ep++){
		printf("%s\n",*ep);
	}

	if(strcmp(argv[1],"set") == 0){
		if(argc == 5){
			setEnv(argv[2],argv[3],atoi(argv[4]));
		}else{
			setEnv(argv[2],argv[3],0);
		}
	}

	if(strcmp(argv[1],"unset") == 0){
		if(unsetEnv(argv[2])== -1){
			printf("unsetEnv Failed.\n");
		}
	}

	for(ep = environ; *ep!=NULL;ep++){
		printf("%s\n",*ep);
	}

	exit(EXIT_SUCCESS);
}		