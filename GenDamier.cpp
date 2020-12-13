#include <iostream>
#include "prototypes.h"

int main(void)
{
    int PID=0, PPID=0;
    int PID1=0;
    int PID2=0;
    int i=0;
    char Case[5];
    while(PID2==0 && i<=9999)
    {
        sprintf(Case,"%4d", i);
        if (GetPIDnPPIDfromFile(&PID, &PPID, Case)!=-1) //Case existe
        {
            if (PID1==0) PID1=PPID;
            else if (PID2==0) PID2=PPID;
        }
        i++;
    }
    Dessiner(PID1,PID2);
}