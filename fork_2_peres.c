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
#include <sys/resource.h>

#define MODE_AFFICHAGE_MERE 0

int getAllChildProcess(pid_t ppid)
{
   int pid=0;
   char *buff = NULL;
   size_t len = 255;
   char command[256] = {0};

   sprintf(command,"ps -ef|awk '$3==%u {print $2}'",ppid);
   FILE *fp = (FILE*)popen(command,"r");
   while(getline(&buff,&len,fp) >= 0)
   {
     printf("%s\n",buff);
   }
    pid=atoi(buff);
   free(buff);
   fclose(fp);
   return pid;
}

void handler(int sig)
{
  pid_t pid;
  int pid2;
    signal(SIGCHLD, SIG_IGN);
  pid = wait(NULL);
    
  printf("FATHER Pid %d exited. (MOTHER PID=%d)\n", pid,getpid());
  if (pid == getpid()+1) pid2=pid+1;
  else pid2=pid-1;
  //pid2=getAllChildProcess(getpid());
  //printf("2nd FATHER PID : %d WON THE PARTY !!\n",pid2);
  SendSIG(pid2,SIGQUIT);//On tue le second pere
    printf("2nd FATHER PID : %d WON THE PARTY !!\n",pid2);
  exit(0);
}

int main() 
{ 
    int pid, pid1, pid2 ; 
    pid_t PERES[2];
    int switch_pipe=0;
    char nom_pipe_Pere1[32]="\0";
    char nom_pipe_Pere2[32]="\0";
    char buff_Pere1[5]={'\0','\0','\0','\0','\0'};
    char buff_Pere2[5]={'\0','\0','\0','\0','\0'};
    // la variable pid recoit et retourne les valeurs données par le fork
    init_Folders();
    printf("\n========================================\n"); 
    printf("+\t\t\t\t\t+\n");
    printf("+\t\t\t\t\t+\n");
    printf("+\t\t\t\t\t+\n");
    printf("+\tStarting the KOMBAT!!\t\t+\n"); 
    printf("+\t\t\t\t\t+\n");
    printf("+\t\t\t\t\t+\n");
    printf("+\t\t\t\t\t+\n");
    printf("\n========================================\n");

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
            signal(SIGCHLD, handler);
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