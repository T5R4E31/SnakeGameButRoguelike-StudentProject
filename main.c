#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "grille.h"
#include "fonction_jeu.h"

int main(int argc, char *argv[]){
  //on veut strictement 4 argument en plus de ./main
  if (argc!=5){
    printf("ERREUR\n Execution : ./main {longueur} {largeur} {delai} {jeu (1 pour serpent)}\n");
    return EXIT_FAILURE;
  }
  
  //a rajouter : test si argv[1], argv[2] et argv[3] sont bien des nombres
  //a rajouter : test contre l'injection
  int length = atoi(argv[1]);
  int width = atoi(argv[2]);
  int delay = atoi(argv[3]);

  //initialisation de ncurses
  initscr();
  raw();
  keypad(stdscr, TRUE);
  noecho();

  halfdelay(delay);

  grille * toto = grilleAllouer(length, width);
  grilleVider(toto); 
  grilleTirageFruit(toto);
  
  //debut de loop de gameplay
  gameLoopSnake(toto);
  
  //fin de ncurses, permet de revenir au terminal normal
  endwin();
  return EXIT_SUCCESS;
}
