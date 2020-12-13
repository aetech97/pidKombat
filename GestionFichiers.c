/*
Fichier GestionFichiers.c
Auteur : Pierre LAGO
Mois/Année : Décembre 2020
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>    
#include "prototypes.h"

#define FOLDER "Cases/"
#define FOLDER_PIPES "Pipes/"
#define FOLDER_PIPES_MERE "PipesMere/"

struct stat st = {0};

int GetPIDnPPIDfromFile(int *PID, int *PPID, char *FileName) // filename ="FOLDER/0000"
{
    int nb=0;
    int Buf;
    //int Fichier = open(FileName, O_RDONLY); //lecture seule
    int Fichier = 0;
    char fic[32]="\0";

    strcat(fic,FOLDER);
    strcat(fic,FileName);
    Fichier = open(fic, O_RDONLY);//lecture seule
    if (Fichier>0)
    {
        nb=read(Fichier, &Buf, sizeof(int));
        //printf("Buf1=%d\n", Buf);
        *PID=Buf;
        nb+=read(Fichier, &Buf, sizeof(int));
        //printf("Buf2=%d\n", Buf);
        *PPID=Buf;
    }
    else
    {    
        //printf("Erreur ouverture %s : %d", FileName, Fichier);
        
    }
    return Fichier;
}

int SetPIDnPPIDfromFile(int PID, int PPID, char *FileName)
{
    int nb=0;
    char fic[32]="\0";
    //int Fichier = open(FileName, O_WRONLY|O_CREAT, S_IWUSR|S_IRUSR); //EcritureSeule
    int Fichier = 0;

    strcat(fic,FOLDER);
    strcat(fic,FileName);
    Fichier = open(fic, O_WRONLY|O_CREAT, S_IWUSR|S_IRUSR); //EcritureSeule

    if (Fichier>0)
    {
        nb=write(Fichier, &PID, sizeof(int));
        nb+=write(Fichier, &PPID, sizeof(int));
    }
    else
        nb=Fichier;
    return nb;
}

int main2(void)
{
    int Case, MonPID=getpid(), MonPPID=getppid();
    for (int i=0; i<100; i++)
    {
        while(Case == GenNombre(9999));
        Case = GenNombre(9999);
        AttaquerCase(MonPPID, MonPID, Case, SIGUSR1);
    }
    return 0;
}    

int SendSIG2(pid_t PID, int Signal) //Envoi signal [SIG_QUIT, SIGUSR1, SIGUSR2] au PID avec kill()
{
    if (Signal==3) 
        printf("J'envoie SIGQUIT a %d\n",PID);
    else
        printf("J'envoie SIGUSR1 a %d\n",PID);
    return 0;
}


int AttaquerCase(int MonPID, int MonPPID, int CaseNumber, int Signal) //Signal = SIGUSR1 pour PERE1 et SIGUSR2 pour PERE2
{
    //int MonPID=1234, MonPPID=7890;
    int PID=0, PPID=0;
    int RetVal=0;
    char Case[5];
    sprintf(Case,"%4d", CaseNumber);
    //SetPIDnPPIDfromFile(MonPID,MonPPID, "0000");
    if (GetPIDnPPIDfromFile(&PID, &PPID, Case)==-1) 
    {
        printf("Le PID %d occupe la case %s\n",MonPID, Case);
        RetVal=SetPIDnPPIDfromFile(MonPID, MonPPID, Case);
        if (RetVal!=2) return 1;
    }    
    else
    {
        if (PPID!=MonPPID)
        {
            printf("Le PID %d vole la case %s au PID %d\n",MonPID, Case,PID);
            //kill adversaire (PID)
            SendSIG(PID, SIGQUIT); //Je tue le fils
            //Send SIGUSR1 PPID
            SendSIG2(PPID, SIGUSR1); //Je signale au pere que j'ai tué un fils
            //approprier fichier
            RetVal=SetPIDnPPIDfromFile(MonPID, MonPPID, Case); // J'écrit mon PID et mon PPID dans la case
            if (RetVal!=2) return 1;
        }
        else
            printf("La case %s appartient deja au PPID %d\n", Case, MonPPID);
    }
    return 0;
}

void init_Folders(void)
{
    //Init le folder avec les cases
    if (stat(FOLDER, &st) == -1) 
    {
        mkdir(FOLDER, 0760);
    }
    SupprimerCases(FOLDER);

    //Init le folder avec les pipes des fils
    if (stat(FOLDER_PIPES, &st) == -1) 
    {
        mkdir(FOLDER_PIPES, 0760);
    }
    SupprimerCases(FOLDER_PIPES);

    //Init le folder avec les pipes des peres
    if (stat(FOLDER_PIPES_MERE, &st) == -1) 
    {
        mkdir(FOLDER_PIPES_MERE, 0760);
    }
    SupprimerCases(FOLDER_PIPES_MERE);
}

