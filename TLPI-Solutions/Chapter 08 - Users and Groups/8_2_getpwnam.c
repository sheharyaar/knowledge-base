#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <pwd.h>

void errExit(char* str){
	printf("Error in %s :\n",str);
	int errvar = errno;
	printf("%s\n",strerror(errvar));
	exit(EXIT_FAILURE);
}

struct passwd* getpwNam(char* str){
	struct passwd* pass;
	pass = getpwent();
	while(pass!=NULL && strcmp(pass->pw_name,str) != 0){
		pass = getpwent();		
	}
	endpwent();
	return pass; 
}

int main(int argc,char* argv[]){
	struct passwd* pass;
	pass = getpwNam(argv[1]);
	errno = 0;
	if(pass == NULL){
		if(errno == 0)
			printf("User not found.\n");
		else
			errExit("getpwNam");
	}else{
		printf("Username : %s\n",pass->pw_name);
		printf("Password : %s\n",pass->pw_passwd);
		printf("UID : %d\n",pass->pw_uid);
		printf("GID : %d\n",pass->pw_gid);
		printf("Gecos : %s\n",pass->pw_gecos);
		printf("Directory : %s\n",pass->pw_dir);
		printf("Shell : %s\n",pass->pw_shell);
	}
	exit(EXIT_SUCCESS);
}