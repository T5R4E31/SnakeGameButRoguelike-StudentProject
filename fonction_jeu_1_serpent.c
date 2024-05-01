#include "fonction_jeu.h"
#include "grille.h"
#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>

void gameLoopSnake(grille * g){
  int input;
  
  //creation d'un serpent avec une position et une couleur arbitraire
  //a rajouter : position aleatoire et couleur aleatoire
  serpent * player = malloc(sizeof(serpent));
  player->head = creerListSection();
  ajouterSectionTete(player->head, creerSection(1, 45));
  player->tete_serpent.x = 1;
  player->tete_serpent.y = 1;

  //on s'assure de vider la grille
  grilleVider(g);
  //on re rempli la grille avec notre serpent actuel
  grilleRemplir(g, player);
  while (input!='#'){
    //on prend l'input clavier de l'utilisateur
    input = getch();
   
    switch (input){
      //deplacement de base de tout jeu video
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
      //touche p pour quitter
      //a rajouter : menu pour les information de gameplay
      case 'p':
        return;
    }
    
    //si le joueur touche un mur, quitte le programme (sans ca le programme segfault)
    if (player->tete_serpent.x == 0 || player->tete_serpent.y == 0){
      return;
    }
    //met le nouveau serpent dans la grille et l'affiche
    grilleRemplir(g, player);
    grilleRedessiner(g);

    //vide la grille pour ne pas avoir de trace de serpent residuelle
    grilleVider(g);
    
    //fflush() s'assure de bien afficher tout ce qu'il y a dans le cache
    fflush(stdout);

  }

  free(player);

}

