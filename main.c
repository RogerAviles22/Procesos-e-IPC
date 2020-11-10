#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_LEN 1024

int main(){

   char* argv[100];        //user command
   char* path= "/bin/";    //set path at bin
   //int argc;               //arg count
   char progpath[20];      //full file path
   char entrada[BUFFER_LEN];  //get command entrada

	while(1){

	    printf("Ingrese el comando>> ");                    //print shell prompt

	    if(!fgets(entrada, BUFFER_LEN, stdin))
	   		break;

		size_t length = strlen(entrada);
		if (entrada[length - 1] == '\n')
	   		entrada[length - 1] = '\0';

	   	if(strcmp(entrada, "exit")==0)           //check if command is exit
	       break;
	   

	   char *token;                  //split command into separate strings
	   token = strtok(entrada," ");
	   int i=0;
	   while(token!=NULL){
	       argv[i]=token;      
	       token = strtok(NULL," ");
	       i++;
	   }
	   argv[i]=NULL;                     //set last value to NULL for execvp

	   //argc=i;                           //get arg count
	   //for(i=0; i<argc; i++)
	   //    printf("%s\n", argv[i]);         //print command/args
	   
	   strcpy(progpath, path);              //copy /bin/ to file path
	   strcat(progpath, argv[0]);           //add program to path

	   for(i=0; i<strlen(progpath); i++){   //delete newentrada
	       if(progpath[i]=='\n'){      
	           progpath[i]='\0';
	       }
	   }
	   //int pid= fork();           //fork child

	   /*if(pid==0)*/
	   if(fork()==0){                //Child
	       execvp(progpath,argv);
	       fprintf(stderr, "¡Invalid command!\n");

	   }else{                     //Parent
	       wait(NULL);
	       printf("OK!\n");
	   }

	}

	return 0;
} 
