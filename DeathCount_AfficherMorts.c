#include <stdio.h>
#include "DeathCount_AfficherMorts.h"

int AfficherMorts(Equipe * team)
{
    printf("L eqipe %s a perdu un fils.\n", team->Nom);
	return 0;
}

int DeathCount(Equipe * team)
{
    team->nbmorts +=1;
    AfficherMorts(team);
	return 0;
}

int main(int argc, char** argv)
{
    Equipe delta, bravo;
    strcpy(delta.Nom , "Delta");
    strcpy(bravo.Nom , "Bravo");
    delta.nbmorts = 0;
    bravo.nbmorts = 0;
    DeathCount(&delta);
    DeathCount(&delta);
    DeathCount(&bravo);
    printf("Nb morts delta : %d \nNb morts bravo : %d", delta.nbmorts, bravo.nbmorts);
    return 0;
}
