#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define LEN_ENTRADA 1024
#define STDIN 0
#define STDOUT 1

//https://stackoverflow.com/questions/33884291/pipes-dup2-and-exec
//https://www.programacion.com.py/escritorio/c/pipes-en-c-linux

int main(){

   char *argv[150];        //Almacena los comandos
   char cmd_ruta[25];      //Almacena el comando y la carpeta /bin ejecutables
   char entrada[LEN_ENTRADA];  //Almacena lo que escribe el usuario
   int argc=0;
   int fd[2];
   pipe(fd);




	while(1){
		printf("Ingrese el comando >> "); 

		if(!fgets(entrada, LEN_ENTRADA, stdin))
		    	return -1;	

    	//Cambiamos el salto de linea por NULL caracter
		size_t length = strlen(entrada);
		if (entrada[length - 1] == '\n')
	   		entrada[length - 1] = '\0';   

	    //Salida del shell-personalizado
	   	if(strcmp(entrada, "exit")==0)
	   		return 0;

	   	//Dividimos el comando por el caracter espacio " "
	    char *token;              
	    token = strtok(entrada," ");
	    int i=0;
	    while(token!=NULL){
	       argv[i]=token;      
	       token = strtok(NULL," ");
	       i++;
	    }
	    argv[i]=NULL;     

	   //copiamos /bin
	   strcpy(cmd_ruta, "/bin/");  
	   //adjuntamos comandos            
	   strcat(cmd_ruta, argv[0]); 

	   	if (fork() == 0) { //reads  

 
		//close(STDOUT); //close stdout
		   dup(fd[1]);  // redirect standard output to the pipe table;
	       close(fd[0]); //parent does not read from pipe
	       close(fd[1]); //closed unused file descriptor
			//char *args[]={"/bin/cat",NULL};
			//execv(cmd_ruta, argv); 
	   		//printf("%s\n", &argv); 
		    execv(cmd_ruta, argv);
	        fprintf(stderr, "¡Comando Inválido!\n"); 
	        exit(0);   
		} else { //writes 
			//close(STDIN); //close stdin
			dup(fd[0]);  // redirect standard input to the pipe table
			close(fd[0]); // closed unused file descriptor
			close(fd[1]); // child does not write to pipe

	       
		   //char *args[]={"/bin/ps",NULL};
	        wait(NULL);
	        printf("OK!\n");
	    }
         	  

	}

	return 0;
} 
