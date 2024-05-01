#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "grille.h"
#include "fonction_jeu.h"

int main(int argc, char *argv[]){
  if (argc!=5){
    printf("ERREUR\n Execution : ./main {longueur} {largeur} {delai} {jeu (1 pour serpent)}\n");
    return EXIT_FAILURE;
  }
  
  int length = atoi(argv[1]);
  int width = atoi(argv[2]);
  int delay = atoi(argv[3]);

  initscr();
  raw();
  keypad(stdscr, TRUE);
  noecho();

  halfdelay(delay);

  grille * toto = grilleAllouer(length, width);
  grilleVider(toto); 
  grilleTirageFruit(toto);
  
  printf("%d %d %d", length, width, delay);

  gameLoopSnake(toto);
  
  endwin();
  return EXIT_SUCCESS;
}
