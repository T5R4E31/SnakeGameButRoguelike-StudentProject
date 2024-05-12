#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "grille.h"
#include "fonction_jeu.h"

#define DELAY 2

int main(int argc, char *argv[]){
  //on veut strictement 4 argument en plus de ./main
  
  //a rajouter : test si argv[1], argv[2] et argv[3] sont bien des nombres
  //a rajouter : test contre l'injection
  int length = 20;
  int width = 25;
  float delay = DELAY;

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
  
  //on defini le delai de chaque etape
  halfdelay(delay);

  //on initialise le choix possible du joueur dans le menu
  int opt = 1;
  int input = 0;
  while (input!='a'){
    printGameMenu(opt);
    fflush(0);
    input = getch();
    if (input == -1){
      continue;
    }
    switch(input){
      case 'z':
        opt = (opt + 1)%2;
        break;
      case 's':
        opt = (opt + 1)%2;
        break;
      case ' ':
        //si le joueur appuie sur espace, on verifie sur quel bouton il est 
        if (opt == 1){
          //initialisation de la grille et demarrage du jeu
          grille * toto = grilleAllouer(length, width);
          grilleVider(toto);
          gameLoopSnake(toto);
          grilleDesallouer(toto);
        }
        if (opt == 0){
          //fin du jeu, on endwin pour revenir au terminal
          endwin();
          return EXIT_SUCCESS;
        }
    }
  }

  //fin de ncurses, permet de revenir au terminal normal
  endwin();
  return EXIT_SUCCESS;
}
