int GenNombre(int NbMax);//Generer Nombre Aleatoire
int GetPIDnPPIDfromFile(int *PID, int *PPID, char *FileName); // filename ="FOLDER/0000"
int SetPIDnPPIDfromFile(int PID, int PPID, char *FileName);
int SendSIG(pid_t PID, int Signal); //Envoi signal [SIG_QUIT, SIGUSR1, SIGUSR2] au PID avec kill()
int SupprimerCases(char *FOLDER); //Supprime toutes les cases (0000 to 9999)
int SendNumber(int Pipe[2], int Nombre); 
int ReadNumber(int Pipe[2], int *Nombre);
int DeathCount(Equipe Team); // a chaque appel, on incrémente le nb de morts de l'equipe désignée. A 5 morts, l'équipe a perdu
int AfficherMorts(Equipe Team); 

typedef struct
{
    pid_t PID_MERE;
    pid_t PID_PERE;
    pid_t PID_FILS[5];
    int nbmorts;
<<<<<<< HEAD
    char Nom[32];
}Equipe;
=======
}Equipe;
>>>>>>> 6338840378d25610284f774819022346a26829c9
