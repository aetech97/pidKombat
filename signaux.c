//
//  signaux.c
//
//  Created by Benjamin Bortolotti on 04/12/2020.
//

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/wait.h>

int SendSIG(pid_t PID, int Signal)
//Envoi signal [SIG_QUIT, SIGUSR1, SIGUSR2] au PID avec kill()

{
    printf("\n\txxxxxxxxxx ATTACKED!!!!xxxxxxxxxx\n");//, Signal, PID);
    kill(PID,Signal);
    wait(NULL);
    return 1;
}


