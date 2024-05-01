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
  start_color();

  init_pair(1, COLOR_BLACK, COLOR_WHITE);
  init_pair(2, COLOR_WHITE, COLOR_BLACK);
  init_pair(4, COLOR_BLACK, COLOR_MAGENTA);
  init_pair(5, COLOR_BLACK, COLOR_GREEN);

  halfdelay(delay);

  grille * toto = grilleAllouer(length, width);
  grilleVider(toto); 
  grilleTirageFruit(toto);
  
  int opt = 1;
  int input = 0;
  while (input!=' '){
    printGameMenu(opt);
    fflush(0);
    input = getch();
    if (input == -1){
      continue;
    }
    switch(input){
      case KEY_UP:
        opt = (opt + 1)%2;
        break;
      case KEY_DOWN:
        opt = (opt + 1)%2;
        break;
      case ' ':
        if (opt == 1){
          gameLoopSnake(toto);
        }
        if (opt == 0){
          endwin();
          return EXIT_SUCCESS;
        }
    }
  }

  //fin de ncurses, permet de revenir au terminal normal
  endwin();
  return EXIT_SUCCESS;
}
