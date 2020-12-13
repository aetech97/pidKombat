//
//  forh_2_peres.c
//
//  Created by Benjamin Bortolotti on 11/12/2020.
//
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/wait.h>
#include "prototypes.h"

#define MODE_AFFICHAGE_MERE 0

int main() 
{ 
<<<<<<< HEAD
    int pid, pid1, pid2 ; 
    int switch_pipe=0;
    char nom_pipe_Pere1[32]="\0";
    char nom_pipe_Pere2[32]="\0";
    char buff_Pere1[5]={'\0','\0','\0','\0','\0'};
    char buff_Pere2[5]={'\0','\0','\0','\0','\0'};
=======
    int pid, pid1; 
>>>>>>> 8ff7fa4706e7e046a445d0cea83509c00a58a911
    // la variable pid recoit et retourne les valeurs données par le fork
    init_Folders();
    printf("Starting the program!!\n"); 

    pid = fork(); // fork un première fois
  
    // Si fork() = 0, c'est donc un process fils 
    if (pid == 0) 
    { 
               // prend le PID du fils1 (papa1)
        sleep(2);   
        printf("papa[1] --> pid = %d and ppid = %d\n", getpid(), getppid());
        pere(1);
        printf("\n");

        
    } 

    // sinon fork du premier fils  
    else 
    { 
        pid1 = fork();      // fork 2
        
        if (pid1 == 0)      // Si fork() = 0, c'est donc un process fils  
        { 
            sleep(2); 
            printf("papa[2] --> pid = %d and ppid = %d\n", getpid(), getppid());
            pere(2);
            printf("\n");
        } 
        else 
        { 
            printf("mere --> pid = %d\n", getpid());

            sprintf(nom_pipe_Pere1,"%d",pid);//On recupere le PID du pere 1 
            sprintf(nom_pipe_Pere2,"%d",pid1);//On recupere le PID du pere 2

            printf("\tNom du pipe cree -> %s\n",nom_pipe_Pere1);
            printf("\tNom du pipe cree -> %s\n",nom_pipe_Pere2);        

            if(initPipeMere(nom_pipe_Pere1)<0)
            {
                printf("ERROR INIT PIPE => %s\n",nom_pipe_Pere1);
            }

            if(initPipeMere(nom_pipe_Pere2)<0)
            {
                printf("ERROR INIT PIPE => %s\n",nom_pipe_Pere2);
            }

            sleep(10);
            
            while(1)
            {

#if MODE_AFFICHAGE_MERE                

                if(switch_pipe==0)
                {
                    //Recuperer les informations provenant des pères... lets use pipes!!!
                    ReadBuff(nom_pipe_Pere1,buff_Pere1); //Lire le buffer du pere 1                
                    //printf("Buffer recu du pere 1 = %s\n",buff_Pere1);
                    printf("\n\t********************ETAT des ENFANTS - PERE 1:********************\n\n");
                    for(int i=0;i<5;i++)
                    {
                        if(buff_Pere1[i]=='O')
                        {
                            printf("\t ENFANT %d => VIVANT ",i+1);
                        }
                        else if (buff_Pere1[i]=='X')
                        {
                            printf("\t ENFANT %d => MORT ",i+1);
                        }
                    }
                    switch_pipe=!switch_pipe;
                }

                else if(switch_pipe==1)
                {
                    ReadBuff(nom_pipe_Pere2,buff_Pere2); //Lire le buffer du pere 2
                    //printf("Buffer recu du pere 2 = %s\n",buff_Pere2);
                    printf("\n\t********************ETAT des ENFANTS - PERE 2:********************\n\n");
                    for(int i=0;i<5;i++)
                    {
                        if(buff_Pere2[i]=='O')
                        {
                            printf("\t ENFANT %d => VIVANT ",i+1);
                        }
                        else if (buff_Pere2[i]=='X')
                        {
                            printf("\t ENFANT %d => MORT ",i+1);
                        }
                    }
                    switch_pipe=!switch_pipe;
                }
#endif
                sleep(1);
            }
        } 
        wait(NULL);
    }
    wait(NULL);
    return 0; 
} 