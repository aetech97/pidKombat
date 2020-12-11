typedef struct
{
    pid_t PID_MERE;
    pid_t PID_PERE;
    pid_t PID_FILS[5];
    int nbmorts;
    char Nom[32];
}Equipe;

int GenNombre(int NbMax);//Generer Nombre Aleatoire
int GetPIDnPPIDfromFile(int *PID, int *PPID, char *FileName); // filename ="FOLDER/0000"
int SetPIDnPPIDfromFile(int PID, int PPID, char *FileName);
int SendSIG(pid_t PID, int Signal); //Envoi signal [SIG_QUIT, SIGUSR1, SIGUSR2] au PID avec kill()
int SupprimerCases(char *FOLDER); //Supprime toutes les cases (0000 to 9999)
int SendNumber(const char *Pipe, int Nombre); 
int ReadNumber(const char *Pipe, int *Nombre);
int DeathCount(Equipe * Team); // a chaque appel, on incrémente le nb de morts de l'equipe désignée. A 5 morts, l'équipe a perdu
int AfficherMorts(Equipe * Team); 
int AttaquerCase(int MonPID, int MonPPID, int CaseNumber, int Signal); //Signal = SIGUSR1 pour PERE1 et SIGUSR2 pour PERE2
int pere(int numero);

int initPipe(const char * Pipe);
int destroyPipe(const char * Pipe);
