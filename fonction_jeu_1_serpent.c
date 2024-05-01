#include "fonction_jeu.h"
#include "grille.h"
#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>

void gameLoopSnake(grille * g){
  int input;
  int last_input;

  serpent * player = malloc(sizeof(serpent));
  player->head = creerListSection();
  ajouterSectionTete(player->head, creerSection(1, 45));
  player->tete_serpent.x = 1;
  player->tete_serpent.y = 1;

  grilleVider(g);
  grilleRemplir(g, player);
  printf("hoi");
  while (input!='#'){
    input = getch();
    
    if (input == -1){
      last_input = -1;
    }
    else{
      last_input = input;
    }

    switch (last_input){
      case 'z':
        --player->tete_serpent.x;
        break;
      case 's':
        ++player->tete_serpent.x;
        break;
      case 'd':
        ++player->tete_serpent.y;
        break;
      case 'q':
        --player->tete_serpent.y;
        break;
      case 'p':
        return;
    }

    if (player->tete_serpent.x == 0 || player->tete_serpent.y == 0){
      return;
    }
    grilleRemplir(g, player);
    grilleRedessiner(g);
    grilleVider(g);
    fflush(stdout);

  }

  free(player);

}

