all: grille.o main.o serpent.o liste_section.o
	gcc -Wall grille.o serpent.o liste_section.o main.o -o main

clean:
	rm *.o main

main.o: main.c
	gcc -Wall -c main.c

grille.o: grille.c
	gcc -Wall -c grille.c

serpent.o: serpent.o
	gcc -Wall -c serpent.c

liste_section.o: liste_section.c
	gcc -Wall -c liste_section.c
