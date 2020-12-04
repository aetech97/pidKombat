#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int pid, pid1, pid2, pid3, pid4, pid5;

    printf("Pere PID = (%d)\n", getpid());

    pid1 = fork();
    if (pid1 == 0)
        {
            sleep(2); 
            printf("Fils[1] PID = (%d) et PPID = (%d) \n", getpid(), getppid());
            return 0;
        }

    pid2 = fork();
    if (pid2 == 0)
        {
            sleep(2); 
            printf("Fils[2] PID = (%d) et PPID = (%d) \n", getpid(), getppid());
            return 0;
        }

    pid3 = fork();
    if (pid3 == 0)
        {
            sleep(2); 
            printf("Fils[3] PID = (%d) et PPID = (%d) \n", getpid(), getppid());
            return 0;
        }

    pid4 = fork();
    if (pid4 == 0)
        {
            sleep(2); 
            printf("Fils[4] PID = (%d) et PPID = (%d) \n", getpid(), getppid());
            return 0;
        }

    pid5 = fork();
    if (pid5 == 0)
        {
            sleep(2); 
            printf("Fils[5] PID = (%d) et PPID = (%d) \n", getpid(), getppid());
            return 0;
        }


    printf("Vérification PID pere = (%d) et PPID = (%d)\n", getpid(),getppid());

    return 0;
}