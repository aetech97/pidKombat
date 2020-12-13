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
#include <errno.h>
#include <string.h>

#include"prototypes.h"

#define UNITARY_TEST 0  // =>1 to launch main test  ;   =>0 to deactivate main code
#define MODE_DEBUG 0  // =>1 to show print  ;   =>0 to deactivate 
struct timespec nanos;

#define FOLDER_PIPES "Pipes/"
#define FOLDER_PIPES_MERE "PipesMere/"

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

//*****************************Start of main to allow unitary tests*****************************
#if UNITARY_TEST
int main(void)
{
    int pid;
    int max_rand=500,rand_nb=0;
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
    return 0;
}
#endif
//*****************************End of main to allow unitary tests*****************************

//Dont call this function too fast, it might return the same number (pay attention to the time and/or threads!!)
int GenNombre(int NbMax)
{
    int number=0,previous=0;
    //srandom(time(0));
    //srandom(clock()+getpid());


    clock_gettime(CLOCK_MONOTONIC, &nanos);
    srandom(nanos.tv_nsec);

    number=random()%NbMax;
    previous=number;
    while(number == previous) 
    {
        srandom(clock()+getpid());

        clock_gettime(CLOCK_MONOTONIC, &nanos);
        srandom(nanos.tv_nsec);
        number=random()%NbMax;
    }
    return number;
}

int initPipe(const char * Pipe)
{
    int stat=0;
    char fic_Pipe[32]="\0";

    strcat(fic_Pipe,FOLDER_PIPES);
    strcat(fic_Pipe,Pipe);

    unlink(fic_Pipe);
    stat=mkfifo(fic_Pipe,0750);
    return stat;
}

int initPipeMere(const char * Pipe)
{
    int stat=0;
    char fic_Pipe[32]="\0";

    strcat(fic_Pipe,FOLDER_PIPES_MERE);
    strcat(fic_Pipe,Pipe);

    unlink(fic_Pipe);
    stat=mkfifo(fic_Pipe,0750);
    return stat;
}

int destroyPipe(const char * Pipe)
{
    int stat=0;
    char fic_Pipe[32]="\0";

    strcat(fic_Pipe,FOLDER_PIPES);
    strcat(fic_Pipe,Pipe);

    stat = unlink(fic_Pipe);
    return stat;
}

int SendNumber(const char *Pipe, int Nombre)
{
    int dp=0;
    int state=0;
    char fic_Pipe[32]="\0";

    strcat(fic_Pipe,FOLDER_PIPES);
    strcat(fic_Pipe,Pipe);

    dp=open(fic_Pipe,O_WRONLY | O_NONBLOCK);           // Ouverture du pipe    
    state=write(dp,&Nombre,sizeof(int));      // Ecriture dans le pipe
    //close(dp);                          // Fermeture du pipe en écriture 
    if(state<=0)
    {
        //Si le pipe n'a pas été ouvert précedemment, le fermer!
        if(errno==ENXIO)
        {
#if MODE_DEBUG            
            printf("ERROR Ecriture PIPE => %s\n",Pipe);
            printf("\tSTATE VALUE => %d\n",state);
            printf("\t***CLOSING PIPE*** => %s\n",Pipe);
#endif             
            close(dp);
        }
        //Si state<=0, rien n'a été écrit, alors le child est compromis!!
        return state;
    }
    return state;                       
}

int ReadNumber(const char *Pipe)
{
    int dp=0;
    int Nombre=0;
    int state=0;
    char fic_Pipe[32]="\0";

    strcat(fic_Pipe,FOLDER_PIPES);
    strcat(fic_Pipe,Pipe);

    dp=open(fic_Pipe,O_RDONLY);          // Ouverture du pipe 
	state=read(dp,&Nombre,sizeof(int));	    // Lecture dans le pipe
    close(dp);                          // Fermeture du pipe en écriture 
    if(state<=0)
    {
#if MODE_DEBUG 
        printf("ERROR Lecture PIPE => %s\n",Pipe);
        printf("\tSTATE VALUE    => %d\n",state);
        printf("\tDP VALUE       => %d\n",dp);      
#endif         
        return -1;
    }
    return Nombre;
}

int SendBuff(const char *Pipe,const char *buffer)
{
    int dp=0;
    int state=0;
    char fic_Pipe[32]="\0";

    strcat(fic_Pipe,FOLDER_PIPES_MERE);
    strcat(fic_Pipe,Pipe);

    dp=open(fic_Pipe,O_WRONLY|O_SYNC);           // Ouverture du pipe    
    state=write(dp,buffer,5);      // Ecriture dans le pipe
    //close(dp);                          // Fermeture du pipe en écriture 
    if(state<=0)
    {
        //Si le pipe n'a pas été ouvert précedemment, le fermer!
        if(errno==ENXIO)
        {
#if MODE_DEBUG            
            printf("ERROR Ecriture PIPE => %s\n",Pipe);
            printf("\tSTATE VALUE => %d\n",state);
            printf("\t***CLOSING PIPE*** => %s\n",Pipe);
#endif             
            
        }
        //Si state<=0, rien n'a été écrit, alors le child est compromis!!
        close(dp);
        return state;
    }
    close(dp);
    return state;                       
}

int ReadBuff(const char *Pipe,char *buffer)
{
    int dp=0;
    int state=0;
    char fic_Pipe[32]="\0";
    char recv_buffer[5];

    strcat(fic_Pipe,FOLDER_PIPES_MERE);
    strcat(fic_Pipe,Pipe);

    dp=open(fic_Pipe,O_RDONLY|O_SYNC);          // Ouverture du pipe 
	state=read(dp,recv_buffer,5);	    // Lecture dans le pipe
    strcpy(buffer,recv_buffer);
    //close(dp);                          // Fermeture du pipe en écriture 
    if(state<=0)
    {
#if MODE_DEBUG        
        printf("ERROR Lecture PIPE => %s\n",Pipe);
        printf("\tSTATE VALUE    => %d\n",state);
        printf("\tDP VALUE       => %d\n",dp);              
#endif         
        //close(dp);
        return state;
    }
    close(dp);
    return 1;
}