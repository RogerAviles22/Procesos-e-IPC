#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){

	pid_t pidF;
	pid_t statusF;
	pidF = fork();

	if(pidF== -1){
	    fprintf(stderr, "¡Error al crear fork!\n");
	    return -1;
	}
	else if (pidF == 0){
		char *args[] = {"bin/ls", NULL}; 
		execv("/bin/sh", args); //Representa el shell del sistema
	    fprintf(stderr, "¡Error al ejecutar comando!\n");
	}
	waitpid(pidF, &statusF, 0);


	return 0;
}