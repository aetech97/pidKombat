#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>


int SupprimerCases(char *FOLDER)
{
	DIR *dir;
	struct dirent *ent;
	char cwd[PATH_MAX];
	getcwd(cwd, sizeof(cwd));
	if ((dir=opendir(FOLDER)))
    {
        chdir(FOLDER);
		while ((ent=readdir(dir)))
		{
            unlink(ent->d_name);
		}
		closedir (dir);
        chdir(cwd);
		return 0;
	}
	else
	{
		return 1;
	}
}

/*
int main(int argc, char** argv)
{
    char path[PATH_MAX] = "C:\\Users\\aelomari\\Documents\\ISEN\\SYSEXP Project\\test\\test"; //Le path peut etre calcul� autommatiquement (getcwd ou argv[0] + nom_dossier_fichiers)
	int result = SupprimerCases(path);
	printf("%d", result);
    return 0;
}
*/