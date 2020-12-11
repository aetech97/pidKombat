//
//  forh_2_peres.c
//
//  Created by Benjamin Bortolotti on 11/12/2020.
//
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/wait.h>
  
int main() 
{ 
    int pid, pid1, pid2 ; 
    // la variable pid recoit et retourne les valeurs données par le fork 

    pid = fork(); // fork un première fois
  
    // Si fork() = 0, c'est donc un process fils 
    if (pid == 0) 
    { 
               // prend le PID du fils1 (papa1)
        sleep(2);   
        printf("papa[1] --> pid = %d and ppid = %d\n", getpid(), getppid());
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

        } 
        else 
        { 
            sleep(3);
            printf("mere --> pid = %d\n", getpid());
        } 
        wait(NULL);
    }
    wait(NULL);
    return 0; 
} 