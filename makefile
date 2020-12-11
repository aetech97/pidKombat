#makefile du partiel d'informatique ALGO2 P17 
#Fichier :       makefile
#Propriétaire :  Pierre LAGO

#Suivi des modifications (du plus récent au plus ancien):
#2020-12-11 : Creation du fichier 

CC = gcc
CFLAGS = -c -lm -Wall -g
LD = gcc
LDFLAGS = 
RM = rm
RMFLAGS = -rf

.PHONY: clean deepclean

main: GestionFichiers.o number_generator.o signaux.o fork_5_fils.o fork_2_peres.o
	$(LD) $(LDFLAGS) $^ -o $@

GestionFichiers.o: GestionFichiers.c
	$(CC) $(CFLAGS) $<

number_generator.o: number_generator.c 
	$(CC) $(CFLAGS) $<

signaux.o: signaux.c 
	$(CC) $(CFLAGS) $<

fork_2_peres.o: fork_2_peres.c 
	$(CC) $(CFLAGS) $<

fork_5_fils.o: fork_5_fils.c 
	$(CC) $(CFLAGS) $<

clean:
	$(RM) $(RMFLAGS) *.o

deepclean: clean
	$(RM) $(RMFLAGS) main