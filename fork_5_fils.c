//
//  forh_5_fils.c
//
//  Created by Benjamin Bortolotti on 04/12/2020.
//
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/wait.h>
#include "prototypes.h"

#define NB_MAX 9999
  
int pere(int numero) 
{ 
    int pid, pid1, pid2, pid3, pid4;
    int rand_nb;
    int nb_fichier[5];
    char nom_pipe[5][32]={"\0","\0","\0","\0","\0"};
    char pipeTab[5][32]={"\0","\0","\0","\0","\0"};
    int etat_fils[5]={0,0,0,0,0};

    // la variable pid recoit et retourne les valeurs données par le fork 

    pid = fork(); // fork un première fois
  
    // Si fork() = 0, c'est donc un process fils 
    if (pid == 0) 
    { 
        /*
        // prend le PID du fils1 
        getpid() ; 
        */

        sleep(1);

        //Creation du pipe
        printf("Pere%dfils[1] --> pid = %d and ppid = %d\n", numero, getpid(), getppid());
        sprintf(nom_pipe[0],"%d_%d",getpid(), getppid());
        printf("\tNom du pipe cree -> %s\n",nom_pipe[0]);        

        if(initPipe(nom_pipe[0])<0)
        {
            printf("ERROR INIT PIPE => %s\n",nom_pipe[0]);
        }
        while (1)
        {
            //sleep(1);
            //Attendre la reception d'un chiffre aléatoire            
            nb_fichier[0]=ReadNumber(nom_pipe[0]);
            //printf("\tFILS: 1 recoit Nb_Rand => %d De => Pere: %d\n", nb_fichier[0],numero);
            if(nb_fichier[0]>=0)
            {
                AttaquerCase(getpid(), getppid(), nb_fichier[0], SIGUSR1);
            }
            

        }
        
    } 

    // sinon fork du premier fils  
    else 
    { 
        pid1 = fork();      // fork 2
        
        if (pid1 == 0)      // Si fork() = 0, c'est donc un process fils  
        { 
            /*
            getpid();       // donne le pid du premier fils
            */

            sleep(2); 
            //Creation du pipe
            printf("Pere%dfils[2] --> pid = %d and ppid = %d\n", numero, getpid(), getppid());
            sprintf(nom_pipe[1],"%d_%d",getpid(), getppid());
            printf("\tNom du pipe cree -> %s\n",nom_pipe[1]);

            if(initPipe(nom_pipe[1])<0)
            {
                printf("ERROR INIT PIPE => %s\n",nom_pipe[1]);
            }
            while (1)
            {                
                nb_fichier[1]=ReadNumber(nom_pipe[1]);
                //printf("\tFILS: 2 recoit Nb_Rand => %d De => Pere: %d\n", nb_fichier[1],numero);
                if(nb_fichier[1]>=0)
                {
                    AttaquerCase(getpid(), getppid(), nb_fichier[1], SIGUSR1);
                }
                
            }
    
        } 
        else 
        { 
            pid2 = fork();  // fork 3
            
            if (pid2 == 0) 
            { 
                /*
                getpid();   // donne le pid du deuxième fils
                */

                sleep(3);
                //Creation du pipe
                printf("Pere%dfils[3] --> pid = %d and ppid = %d\n", numero, getpid(), getppid());
                sprintf(nom_pipe[2],"%d_%d",getpid(), getppid());
                printf("\tNom du pipe cree -> %s\n",nom_pipe[2]);

                if(initPipe(nom_pipe[2])<0)
                {
                    printf("ERROR INIT PIPE => %s\n",nom_pipe[2]);
                }
                while (1)
                {                    
                    nb_fichier[2]=ReadNumber(nom_pipe[2]);
                    //printf("\tFILS: 3 recoit Nb_Rand => %d De => Pere: %d\n", nb_fichier[2],numero);
                    if(nb_fichier[2]>=0)
                    {
                        AttaquerCase(getpid(), getppid(), nb_fichier[2], SIGUSR1);
                    }
                    
                }
        

            }
            else
            { 
                pid3 = fork(); //fork 4
                
                if (pid3 == 0)
                {
                    /*
                    getpid();
                    */

                    sleep(4);
                    //Creation du pipe
                    printf("Pere%dfils[4] --> pid = %d and ppid = %d\n", numero, getpid(), getppid());
                    sprintf(nom_pipe[3],"%d_%d",getpid(), getppid());
                    printf("\tNom du pipe cree -> %s\n",nom_pipe[3]);

                    if(initPipe(nom_pipe[3])<0)
                    {
                        printf("ERROR INIT PIPE => %s\n",nom_pipe[3]);
                    }
                    while (1)
                    {
                        nb_fichier[3]=ReadNumber(nom_pipe[3]);
                        //printf("\tFILS: 4 recoit Nb_Rand => %d De => Pere: %d\n", nb_fichier[3],numero);
                        if(nb_fichier[3]>=0)
                        {
                            AttaquerCase(getpid(), getppid(), nb_fichier[3], SIGUSR1);
                        }
                        
                    }
 
                }
                else
                {
                    pid4 = fork(); //fork 5
                    
                    if (pid4 == 0) 
                    { 
                        /*
                        getpid();
                        */

                        sleep(5);
                        //Creation du pipe
                        printf("Pere%dfils[5] --> pid = %d and ppid = %d\n", numero, getpid(), getppid());
                        sprintf(nom_pipe[4],"%d_%d",getpid(), getppid());
                        printf("\tNom du pipe cree -> %s\n",nom_pipe[4]);

                        if(initPipe(nom_pipe[4])<0)
                        {
                            printf("ERROR INIT PIPE => %s\n",nom_pipe[4]);
                        }
                        while (1)
                        {
                            nb_fichier[4]=ReadNumber(nom_pipe[4]);
                            //printf("\tFILS: 5 recoit Nb_Rand => %d De => Pere: %d\n", nb_fichier[4],numero);
                            if(nb_fichier[4]>=0)
                            {
                                AttaquerCase(getpid(), getppid(), nb_fichier[4], SIGUSR1);
                            }

                        }
                
                    }
                    else
                    {                         
                        printf("parent --> pid = %d\n", getpid());
                        printf("Pere%dfils[1] --> pid = %d and ppid = %d\n", numero, getpid(),pid);
                        sprintf(pipeTab[0],"%d_%d",pid, getpid());
                        printf("Pere%dfils[2] --> pid = %d and ppid = %d\n", numero, getpid(),pid1);
                        sprintf(pipeTab[1],"%d_%d",pid1, getpid());
                        printf("Pere%dfils[3] --> pid = %d and ppid = %d\n", numero, getpid(),pid2);
                        sprintf(pipeTab[2],"%d_%d",pid2, getpid());
                        printf("Pere%dfils[4] --> pid = %d and ppid = %d\n", numero, getpid(),pid3);
                        sprintf(pipeTab[3],"%d_%d",pid3, getpid());
                        printf("Pere%dfils[5] --> pid = %d and ppid = %d\n", numero, getpid(),pid4);
                        sprintf(pipeTab[4],"%d_%d",pid4, getpid());
                        //Attendre l'initialisation de chaque fils et chaque PIPE
                        sleep(8);
                        printf("Tous les fils initialises!!\n");
                        //Executer une boucle for pour envoyer un nb aléatoire à chaque fils
                        while(1)
                        {
                            for(int i=0;i<5;i++)
                            {
                                while(rand_nb==GenNombre(NB_MAX));
                                rand_nb=GenNombre(NB_MAX);
                                //printf("Pere : %d ENVOIE %d A => Fils : %s",numero,rand_nb,pipeTab[i]);
                                etat_fils[i]=SendNumber(pipeTab[i], rand_nb);
                                sleep(1);
                            }
                            sleep(1);
                            printf("\n\t********************ETAT des ENFANTS - PERE %d (PID=%d):********************\n\n",numero, getpid());
                            for(int i=0;i<5;i++)
                            {
                                if(etat_fils[i]!=-1)
                                {
                                    printf("\t ENFANT %d => VIVANT ",i+1);
                                }
                                else
                                {
                                    printf("\t ENFANT %d => MORT ",i+1);
                                }
                            }
                            printf("\n\n");

                        }
                    } 
                    wait(NULL);

                }
                wait(NULL);
                    
            }
            wait(NULL);    
        } 
        wait(NULL);
    }
    wait(NULL);
    return 0; 
} 