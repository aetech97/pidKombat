#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>

int main(void)
{
	int des;
	int pid;
	char buf[7];
	int nb_recv;

	des=open("pipe1",O_RDONLY);
	read(des,&nb_recv,sizeof(int));
	printf("Child here, i received => %d\n",nb_recv);
	close(des);                 // Fermeture du pipe en écriture
	printf("\nChild process ***DONE***!\n");
	exit(0);
}
