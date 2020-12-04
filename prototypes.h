int GenNombre(int NbMax);//Generer Nombre Aleatoire
int GetPIDnPPIDfromFile(int *PID, int *PPID, char *FileName); // filename ="FOLDER/0000"
int SetPIDnPPIDfromFile(int PID, int PPID, char *FileName);
int SendSIG(pid_t PID, int Signal); //Envoi signal [SIG_QUIT, SIGUSR1, SIGUSR2] au PID avec kill()
int SupprimerCases(char *FOLDER); //Supprime toutes les cases (0000 to 9999)
int SendNumber(int Pipe[2], int Nombre); 
int ReadNumber(int Pipe[2], int *Nombre);
int DeathCount(int Team); // a chaque appel, on incrémente le nb de morts de l'equipe désignée. A 5 morts, l'équipe a perdu

typedef struct Equipe
{
    pid_t PID_MERE;
    pid_t PID_PERE;
    pid_t PID_FILS[5];
    int nbmorts;
}

int SupprimerCases(char *FOLDER)
{
	//il faut un #include <unistd.h> et #include <dirent.h>
	DIR *dir;
	struct dirent *ent;
	if (dir = opendir (FOLDER)) {
		while ((ent = readdir(dir)))
		{
			if (!unlink(ent, d_name))
			{
				return 1;
			}
		}
		closedir (dir);
		return 0;
	}
	else 
	{
		return 1;
	}
}