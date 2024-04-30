all: grille.o main.o
	gcc -Wall grille.o main.o -o main

clean:
	rm *.o main

main.o: main.c
	gcc -Wall -c main.c

grille.o: grille.c
	gcc -Wall -c grille.c
