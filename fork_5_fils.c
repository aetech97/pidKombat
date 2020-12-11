//
//  forh_5_fils.c
//
//  Created by Benjamin Bortolotti on 04/12/2020.
//
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/wait.h>
  
int pere(int numero) 
{ 
    
    int pid, pid1, pid2, pid3, pid4, pid5; 
    // la variable pid recoit et retourne les valeurs données par le fork 

    pid = fork(); // fork un première fois
  
    // Si fork() = 0, c'est donc un process fils 
    if (pid == 0) 
    { 
        /*
        // prend le PID du fils1 
        getpid() ; 
        */

        sleep(2);   
        printf("fils[1] --> pid = %d and ppid = %d\n", getpid(), getppid());
        printf("\n");
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
            printf("fils[2] --> pid = %d and ppid = %d\n", getpid(), getppid());

        } 
        else 
        { 
            pid2 = fork();  // fork 3
            
            if (pid2 == 0) 
            { 
                /*
                getpid();   // donne le pid du deuxième fils
                */

                sleep(2);
                printf("fils[3] --> pid = %d and ppid = %d\n", getpid(), getppid());


            }
            else
            { 
                pid3 = fork(); //fork 4
                
                if (pid3 == 0)
                {
                    /*
                    getpid();
                    */

                    sleep(2);
                    printf("fils[4] --> pid = %d and ppid = %d\n", getpid(), getppid());
                }
                else
                {
                    pid4 = fork(); //fork 5
                    
                    if (pid4 == 0) 
                    { 
                        /*
                        getpid();
                        */

                        sleep(2);
                        printf("fils[5] --> pid = %d and ppid = %d\n", getpid(), getppid());
                    }
                    else
                    { 
                        sleep(3);
                        printf("parent --> pid = %d\n", getpid());
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