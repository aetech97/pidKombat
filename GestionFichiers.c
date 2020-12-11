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

int GetPIDnPPIDfromFile(int *PID, int *PPID, char *FileName) // filename ="FOLDER/0000"
{
    int nb=0;
    int Buf;
    int Fichier = open(FileName, O_RDONLY); //lecture
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
        //return Fichier;
    }
    return Fichier;
}

int SetPIDnPPIDfromFile(int PID, int PPID, char *FileName)
{
    int nb=0;
    int Fichier = open(FileName, O_WRONLY|O_CREAT, S_IWUSR|S_IRUSR); //EcritureSeule
    if (Fichier>0)
    {
        nb=write(Fichier, &PID, sizeof(int));
        nb+=write(Fichier, &PPID, sizeof(int));
    }
    else
        nb=Fichier;
    return nb;
}

int main(void)
{
    int Case, MonPID=getpid(), MonPPID=getppid();
    printf("MonPID : %d \t Mon PPID : %d", MonPID, MonPPID);
    getchar();
    for (int i=0; i<100; i++)
    {
        while(Case == GenNombre(9999));//Pour ne pas utiliser plusieurs fois le même nombre aléatoire
        Case = GenNombre(9999);
        AttaquerCase(MonPID, MonPPID, Case, SIGUSR1); //Attaquer case
    }
}    

int SendSIG2(pid_t PID, int Signal) //Envoi signal [SIG_QUIT, SIGUSR1, SIGUSR2] au PID avec kill()
{
    char *NomSignal;
    if (Signal==3) NomSignal="SIGQUIT";
    else NomSignal="SIGUSR1";
    printf("J'envoie %s a %d\n",NomSignal,PID);
    return 1;
}


int AttaquerCase(int MonPID, int MonPPID, int CaseNumber, int Signal) //Signal = SIGUSR1 pour PERE1 et SIGUSR2 pour PERE2
{
    //int MonPID=1234, MonPPID=7890;
    int PID=0, PPID=0;
    int RetVal=0;
    char Case[4];
    sprintf(Case,"%4d", CaseNumber);//Conversion du CaseNumber en char
    //SetPIDnPPIDfromFile(MonPID,MonPPID, "0000");
    if (GetPIDnPPIDfromFile(&PID, &PPID, Case)==-1) //La case est occupée ?
    {
        printf("Le PID %d occupe la case %s\n",MonPID, Case); //si libre, j'occupe la case
        RetVal=SetPIDnPPIDfromFile(MonPID, MonPPID, Case);
        if (RetVal!=2) return 1;
    }    
    else
    {
        if (PPID!=MonPPID) //sinon, je vérifie qu'elle n'appartient pas a mon frère
        {
            printf("Le PID %d vole la case %s au PID %d\n",MonPID, Case,PID); //je vole la case
            //kill adversaire (PID)
            SendSIG(PID, SIGQUIT); //Je tue le fils
            //Send SIGUSR1 PPID
            SendSIG2(PPID, SIGUSR1); //Je signale au pere que j'ai tué un fils
            //approprier fichier
            RetVal=SetPIDnPPIDfromFile(MonPID, MonPPID, Case); // J'écrit mon PID et mon PPID dans la case
            if (RetVal!=2) return 1;
        }
        else
            printf("La case %s appartient deja au PPID %d\n", Case, MonPPID); // Je laisse la case à mon frère
    }
    return 0;
}

