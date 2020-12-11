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
    int nb_fichier,rand_nb;
    char nom_pipe[32]="";

    for(int i=1;i<6;i++)
    {
        sprintf(nom_pipe,"Pere%dFils%d",numero,i);
        initPipe(nom_pipe);
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
        sprintf(nom_pipe,"Pere%dFils1",numero);
        while (1)
        {
            //sleep(1);
            //Attendre la reception d'un chiffre aléatoire            
            nb_fichier=ReadNumber(nom_pipe);
            AttaquerCase(getpid(), getppid(), nb_fichier, SIGUSR1);

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
            sprintf(nom_pipe,"Pere%dFils2",numero);
            while (1)
            {                
                nb_fichier=ReadNumber(nom_pipe);
                AttaquerCase(getpid(), getppid(), nb_fichier, SIGUSR1);
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
                sprintf(nom_pipe,"Pere%dFils3",numero);
                while (1)
                {                    
                    nb_fichier=ReadNumber(nom_pipe);
                    AttaquerCase(getpid(), getppid(), nb_fichier, SIGUSR1);
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
                    sprintf(nom_pipe,"Pere%dFils4",numero);
                    while (1)
                    {
                        nb_fichier=ReadNumber(nom_pipe);
                        AttaquerCase(getpid(), getppid(), nb_fichier, SIGUSR1);
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
                        sprintf(nom_pipe,"Pere%dFils5",numero);
                        while (1)
                        {
                            nb_fichier=ReadNumber(nom_pipe);
                            AttaquerCase(getpid(), getppid(), nb_fichier, SIGUSR1);
                        }
                
                    }
                    else
                    {                         
                        printf("parent --> pid = %d\n", getpid());
                        //Executer une boucle for pour envoyer un nb aléatoire à chaque fils
                        for(int i=1;i<6;i++)
                        {
                            sprintf(nom_pipe,"Pere%dFils%d",numero,i);
                            rand_nb=GenNombre(NB_MAX);
                            SendNumber(nom_pipe, rand_nb);
                            sleep(1);
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