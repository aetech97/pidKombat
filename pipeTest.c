#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>

#include "prototypes.h"

int main(void)
{
	int nb_recv,dp;

    nb_recv=ReadNumber("pipe1");

    //dp=open("pipe1",O_RDONLY);          // Ouverture du pipe 
	//read(dp,&nb_recv,sizeof(int));	    // Lecture dans le pipe 
	//close(dp);                          // Fermeture du pipe en écriture

	printf("Child here, i received => %d\n",nb_recv);
	printf("\nChild process ***DONE***!\n");
	exit(0);
}

int ReadNumber(const char *Pipe)
{
    int dp;
    int Nombre;
    dp=open(Pipe,O_RDONLY);          // Ouverture du pipe 
	read(dp,&Nombre,sizeof(int));	    // Lecture dans le pipe 
	close(dp);                          // Fermeture du pipe en écriture
    return Nombre;
}
