typedef struct
{
	char Nom[30];
    int PID_MERE; //Remplacer int part pid_t
    int PID_PERE; //Remplacer int part pid_t
    int PID_FILS[5]; //Remplacer int part pid_t
    int nbmorts;
}Equipe;

int AfficherMorts(Equipe * team);

int DeathCount(Equipe * team);

