#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define LEN_ENTRADA 1024

int main(){

   char *argv[150];        //Almacena los comandos
   char cmd_ruta[25];      //Almacena el comando y la carpeta /bin ejecutables
   char entrada[LEN_ENTRADA];  //Almacena lo que escribe el usuario
   int argc=0;

	while(1){

		//Entra en el bucle en caso que el usuario presione Enter o no escriba un comando
		do{
			printf("Ingrese el comando >> ");     

			//Recibe los datos escritos en shell
		    if(!fgets(entrada, LEN_ENTRADA, stdin)){
		    	return -1;	    
		    }

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
		   argc=i;

		   //Validamos que haya al menos 1 comando escrito
		   if(i==0){
		       fprintf(stderr, "Escriba más de 1 comando!\n");	 
		   }

		}while(argc==0);

	   //copiamos /bin
	   strcpy(cmd_ruta, "/bin/");  
	   //adjuntamos comandos            
	   strcat(cmd_ruta, argv[0]);              

	   for(int i=0; i<strlen(cmd_ruta); i++){   
	       if(cmd_ruta[i]=='\n'){      
	           cmd_ruta[i]='\0';
	       }
	   }

	   if(fork()==0){                
	       execvp(cmd_ruta,argv);
	       fprintf(stderr, "¡Comando Inválido!\n");

	   }else{                     
	       wait(NULL);
	       printf("OK!\n");
	   }

	}

	return 0;
} 
