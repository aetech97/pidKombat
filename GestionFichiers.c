#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>    

int GetPIDnPPIDfromFile(int *PID, int *PPID, char *FileName) // filename ="FOLDER/0000"
{
    int nb=0;
    int Buf;
    int Fichier = open(FileName, O_RDONLY); //lecture
    if (Fichier>0)
    {
        nb=read(Fichier, &Buf, sizeof(int));
        printf("Buf1=%d\n", Buf);
        *PID=Buf;
        nb+=read(Fichier, &Buf, sizeof(int));
        printf("Buf2=%d\n", Buf);
        *PPID=Buf;
    }
    else
    {    
        printf("Erreur ouverture %s : %d", FileName, Fichier);
        return Fichier;
    }
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
    int PID=0, PPID=0;
    SetPIDnPPIDfromFile(6789,1234, "0000");
    GetPIDnPPIDfromFile(&PID, &PPID, "0000");
    printf("PID:%4d - PPID:%4d\n", PID, PPID);
}
