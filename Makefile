all: grille.o main.o serpent.o liste_section.o objet.o fonction_jeu_1_serpent.o
	gcc -Wall -lncurses fonction_jeu_1_serpent.o objet.o grille.o serpent.o liste_section.o main.o -o main

clean:
	rm *.o main

main.o: main.c
	gcc -Wall -c main.c

grille.o: grille.c
	gcc -Wall -lncurses -c grille.c

serpent.o: serpent.o
	gcc -Wall -c serpent.c

liste_section.o: liste_section.c
	gcc -Wall -c liste_section.c

objet.o: objet.c 
	gcc -Wall -lncurses -c objet.c

fonction_jeu_1_serpent.o:
	gcc -Wall -lncurses -c fonction_jeu_1_serpent.c
