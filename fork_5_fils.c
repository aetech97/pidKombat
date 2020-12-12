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
    int pid, pid1, pid2, pid3, pid4, pid5;
    int rand_nb;
    int nb_fichier[5];
    char nom_pipe[32]="";
    char nom_pipe1[32]="";
    char nom_pipe2[32]="";
    char nom_pipe3[32]="";
    char nom_pipe4[32]="";
    char nom_pipe5[32]="";

    for(int i=1;i<6;i++)
    {
        sprintf(nom_pipe,"Pere%dFils%d",numero,i);        
        if(initPipe(nom_pipe)<0)
        {
            printf("ERROR INIT PIPE => %s\n",nom_pipe);
        }
    }

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
        printf("Pere%dfils[1] --> pid = %d and ppid = %d\n", numero, getpid(), getppid());
        sprintf(nom_pipe1,"Pere%dFils1",numero);
        while (1)
        {
            //sleep(1);
            //Attendre la reception d'un chiffre aléatoire            
            nb_fichier[0]=ReadNumber(nom_pipe1);
            printf("FILS: 1 recoit Nb_Rand => %d\n", nb_fichier[0]);
            printf("\tPere: %d\n",numero);
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
            printf("Pere%dfils[2] --> pid = %d and ppid = %d\n",numero, getpid(), getppid());
            sprintf(nom_pipe2,"Pere%dFils2",numero);
            while (1)
            {                
                nb_fichier[1]=ReadNumber(nom_pipe2);
                printf("FILS: 2 recoit Nb_Rand => %d\n", nb_fichier[1]);
                printf("\tPere: %d\n",numero);
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
                printf("Pere%dfils[3] --> pid = %d and ppid = %d\n", numero, getpid(), getppid());
                sprintf(nom_pipe3,"Pere%dFils3",numero);
                while (1)
                {                    
                    nb_fichier[2]=ReadNumber(nom_pipe3);
                    printf("FILS: 3 recoit Nb_Rand => %d\n", nb_fichier[2]);
                    printf("\tPere: %d\n",numero);
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
                    printf("Pere%dfils[4] --> pid = %d and ppid = %d\n", numero, getpid(), getppid());
                    sprintf(nom_pipe4,"Pere%dFils4",numero);
                    while (1)
                    {
                        nb_fichier[3]=ReadNumber(nom_pipe4);
                        printf("FILS: 4 recoit Nb_Rand => %d\n", nb_fichier[3]);
                        printf("\tPere: %d\n",numero);
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
                        printf("Pere%dfils[5] --> pid = %d and ppid = %d\n", numero, getpid(), getppid());
                        sprintf(nom_pipe5,"Pere%dFils5",numero);
                        while (1)
                        {
                            nb_fichier[4]=ReadNumber(nom_pipe5);
                            printf("FILS: 5 recoit Nb_Rand => %d\n", nb_fichier[4]);
                            printf("\tPere: %d\n",numero);
                            if(nb_fichier[4]>=0)
                            {
                                AttaquerCase(getpid(), getppid(), nb_fichier[4], SIGUSR1);
                            }

                        }
                
                    }
                    else
                    {                         
                        printf("parent --> pid = %d\n", getpid());
                        //Executer une boucle for pour envoyer un nb aléatoire à chaque fils
                        while(1)
                        {
                            for(int i=1;i<6;i++)
                            {
                                sprintf(nom_pipe,"Pere%dFils%d",numero,i);
                                while(rand_nb==GenNombre(NB_MAX));
                                rand_nb=GenNombre(NB_MAX);
                                SendNumber(nom_pipe, rand_nb);
                                sleep(1);
                                printf("Pere: %d envoie Nb_Rand => %d\n", numero,rand_nb);
                            }
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