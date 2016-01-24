##VARIABLES##

CC=gcc
CFLAGS=-Wall -O -lgraph
EXEC=main
HFILES=jeu.h affichage.h constantes.h structures.h

##REGLES##

all: $(EXEC)

main: jeu.o affichage.o main.o
	$(CC) -o main jeu.o affichage.o main.o $(CFLAGS)
jeu.o: jeu.c $(HFILES)
	$(CC) -c jeu.c 
affichage.o: affichage.c $(HFILES)
	$(CC) -c affichage.c 
main.o: main.c $(HFILES)
	$(CC) -c main.c 
clean:
	rm -f *.o core
mrproper: clean
	rm -f $(EXEC)
