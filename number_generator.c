/*
    NUMBER GENERATOR
    Written by: Hector SILVA DIAZ

*/

#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<fcntl.h>
#include<stdio.h>
#include <sys/stat.h>

#include"prototypes.h"

#define UNITARY_TEST 0  // =>1 to launch main test  ;   =>0 to deactivate main code

//Team 1 Pipes
const char *E1_PIPE_1= "pipe1";
const char *E1_PIPE_2= "pipe2";
const char *E1_PIPE_3= "pipe3";
const char *E1_PIPE_4= "pipe4";
const char *E1_PIPE_5= "pipe5";

//Team 2 Pipes
const char *E2_PIPE_1= "pipe6";
const char *E2_PIPE_2= "pipe7";
const char *E2_PIPE_3= "pipe8";
const char *E2_PIPE_4= "pipe9";
const char *E2_PIPE_5= "pipe10";

//Function to initialize A pipe
int initPipe(const char *Pipe);
int destroyPipe(const char *Pipe);

//*****************************Start of main to allow unitary tests*****************************
#if UNITARY_TEST
void main()
{
    int desc[2];
    int pid;
    char buf[7];
    int max_rand=500,rand_nb=0;
    int dp;
    int pipe_nb;

    const char *team1_pipes[5]={E1_PIPE_1,E1_PIPE_2,E1_PIPE_3,E1_PIPE_4,E1_PIPE_5};
    const char *team2_pipes[5]={E2_PIPE_1,E2_PIPE_2,E2_PIPE_3,E2_PIPE_4,E2_PIPE_5};

    //Init the pipes here!!
    for(int i=0;i<5;i++)
    {
        initPipe(team1_pipes[i]);
        initPipe(team2_pipes[i]);
    }

    printf("Welcome to the random number generator!!\n");
    //printf("Please type the maximum possible random number:\n");
    //scanf("%d",&max_rand);
    rand_nb=GenNombre(max_rand);
    printf("The generated random number between 0 and %d is => %d\n",max_rand,rand_nb);
    printf("The adress of the generated number is => %d\n",&rand_nb);

    printf("Please type the number of pipe to use:\n");
    scanf("%d",&pipe_nb);

    pid = fork();

    if (pid == 0) 
    {
        //Launch Child program to send the generated random number through the pipe
        printf("\nChild process here!\n");
        execv("pipeTest",NULL);        
    } 
    
    else 
    {        
        printf("\nParent process sends number...\n");
        SendNumber(team1_pipes[pipe_nb],rand_nb);  //Put write to pipe function here
        wait(0);
        printf("\nParent process ***DONE***\n");
    }
}
#endif
//*****************************End of main to allow unitary tests*****************************

//Dont call this function too fast, it might return the same number (pay attention to the time and/or threads!!)
int GenNombre(int NbMax)
{
    int number,previous;
    srandom(time(0));
    number=random()%NbMax;
    previous=number;
    while(number == previous) 
    {
        srandom(time(0));
        number=random()%NbMax);
    }
    return number;
}

int initPipe(const char * Pipe)
{
    int stat;
    unlink(Pipe);
    stat=mkfifo(Pipe,0666);
    return stat;
}

int destroyPipe(const char * Pipe)
{
    int stat;
    stat = unlink(Pipe);
    return stat;
}

int SendNumber(const char *Pipe, int Nombre)
{
    int dp;
    dp=open(Pipe,O_WRONLY);           // Ouverture du pipe 
    write(dp,&Nombre,sizeof(int));      // Ecriture dans le pipe
    close(dp);                          // Fermeture du pipe en écriture                        
}

int ReadNumber(const char *Pipe, int *Nombre)
{
    int dp;
    dp=open(Pipe,O_RDONLY);          // Ouverture du pipe 
	read(dp,&Nombre,sizeof(int));	    // Lecture dans le pipe 
	close(dp);                          // Fermeture du pipe en écriture
}