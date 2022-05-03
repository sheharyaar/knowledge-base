#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>

static jmp_buf env;

int f1(void){
	switch(setjmp(env)){
		case 0 : {
			printf("setting jump location and exiting function\n");
		}break;
		case 69 : {
			printf("jumped to the function\n");
		}break;
	}
	printf("exited\n");
	return 0;
}

int f2(void){
	longjmp(env,69);
	return 0;
}


int main(){
	f1();
	f2();
	exit(EXIT_SUCCESS);
}