#include "fonction_jeu.h"
#include "grille.h"
#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void gameLoopSnake(grille * g){
  int input = -1;
  int last_input = 'd';
  int score = 0;
  listSection * tmp = malloc(sizeof(listSection));
  
  //creation d'un serpent avec une position et une couleur arbitraire
  //a rajouter : position aleatoire et couleur aleatoire
  serpent * player = malloc(sizeof(serpent));
  player->head = creerListSection();
  player->tete_serpent.x = 1;
  player->tete_serpent.y = 1;
  ajouterSectionTete(player->head, creerSection(1, 45, player->tete_serpent));

  //on s'assure de vider la grille
  grilleVider(g);
  //on re rempli la grille avec notre serpent actuel
  grilleRemplir(g, player);
  //on effectue le tirage pour le premier fruit
  grilleTirageFruit(g);
  while (input!='#'){
    //on prend l'input clavier de l'utilisateur
    switch (input){
      //deplacement de base de tout jeu video
      //on deplace la tete du serpent en fonction des entrees joueurs
      //a chaque tour, on fait disparaitre la queue et on rajoute une case à la tete,
      //afin de deplacer d'une case le serpent
      //si on a mange un fruit, on ne fait pas disparaitre la derniere case 
      //on fait cela pour chaque input possible
      case 'z':
        --player->tete_serpent.x;
        last_input = input;
        ajouterSectionTete(player->head, creerSection(1, 45, player->tete_serpent));
        if (serpentMangeFruit(g, player)){
          score++; 
          break;
        }
        tmp = dernierListSection(player->head);
        avantDernierListSection(player->head)->next = NULL;
        desallouerListSection(tmp);
        break;
      case 's':
        ++player->tete_serpent.x;
        last_input = input;
        ajouterSectionTete(player->head, creerSection(1, 45, player->tete_serpent));
        if (serpentMangeFruit(g, player)){ 
          score++; 
          break;
        }
        tmp = dernierListSection(player->head);
        avantDernierListSection(player->head)->next = NULL;
        desallouerListSection(tmp);
        break;
      case 'd':
        ++player->tete_serpent.y;
        last_input = input;
        ajouterSectionTete(player->head, creerSection(1, 45, player->tete_serpent));
        if (serpentMangeFruit(g, player)){
          score++; 
          break;
        }
        tmp = dernierListSection(player->head);
        avantDernierListSection(player->head)->next = NULL;
        desallouerListSection(tmp);
        break;
      case 'q':
        --player->tete_serpent.y;
        last_input = input;
        ajouterSectionTete(player->head, creerSection(1, 45, player->tete_serpent));
        if (serpentMangeFruit(g, player)){
          score++;
          break;
        }
        tmp = dernierListSection(player->head);
        avantDernierListSection(player->head)->next = NULL;
        desallouerListSection(tmp);
        break;
      //touche p pour quitter
      //a rajouter : menu pour les information de gameplay
      case 'p':
        return;
        break;
      default:
        input = last_input;
        continue;
    }
    
    input = getch();


    //si le joueur touche un mur, on retourne a l'ecran titre (sans ca le programme segfault)
    if (player->tete_serpent.x == -1 || player->tete_serpent.y == 0 || player->tete_serpent.x == g->n || player->tete_serpent.y == g->m-1){
      desallouerListSection(player->head);
      player->head = NULL;
      free(player);
      return;
    }
    
    //si le joueur se touche, on retourne a l'ecran titre
    if (!strcmp(g->grid[player->tete_serpent.x][player->tete_serpent.y], "serp")){
      desallouerListSection(player->head);
      player->head = NULL;
      free(player);
      return;
    }
    
    //on vide dans un premier temps la grille pour eviter les traces de serpent
    grilleVider(g);

    //met le nouveau serpent dans la grille et l'affiche
    grilleRemplir(g, player);
    grilleRedessiner(g);

    
    //fflush() s'assure de bien afficher tout ce qu'il y a dans le cache
    fflush(stdout);

  }

  free(player);

}

//affichage du menu de debut de jeu
void printGameMenu(int opt){
  clear();
  int x, y;
  x = getmaxx(stdscr)/2 - 78/2;
  y = getmaxy(stdscr)/3;
  move(y, x);
  attron(COLOR_PAIR(2));
  printw(" _____  _   _  ___       ___    _   _  ___    _   _     ___    _____         ___ ");
  move(y+1, x);
  printw("(_   _)( ) ( )(  _`\\    (  _`\\ ( ) ( )(  _`\\ ( ) ( )   (  _`\\ (  _  )/'\\_/`\\(  _`\\ ");
  move(y+2, x);
  printw("  | |  | |_| || (_(_)   | (_(_)| `\\| || (_(_)| |/'/'   | ( (_)| (_) ||     || (_(_)");
  move(y+3, x);
  printw(" | |  |  _  ||  _)_    `\\__ \\ | , ` ||  _)_ | , <     | |___ |  _  || (_) ||  _)_ ");
  move(y+4, x);
  printw("  | |  | | | || (_( )   ( )_) || |`\\ || (_( )| |\\`\\    | (_, )| | | || | | || (_( ) ");
  move(y+5, x);
  printw(" (_)  (_) (_)(____/'   `\\____)(_) (_)(____/'(_) (_)   (____/'(_) (_)(_) (_)(____/'");
  
  y = y+6;
  x = getmaxx(stdscr)/2;
  move(y, x - 30/2);
  printw("Programme par : Kylian Maouchi");
  move(y+1, x - 36/2);
  printw("Appuyez sur espace pour selectionner");
  move(y+2, x - 55/2);
  printw("Utilisez les fleches haut et bas pour choisir une option!");
  move(y+3, x);
  y = y+5;
  x = x - 7/2;
  switch (opt){
    case 1:
      move(y+1, x);
      attron(COLOR_PAIR(1));
      printw("Jouer!!");
      move(y+3, x);
      attron(COLOR_PAIR(2));
      printw("Quitter");
      break;
      ;;
    case 0:
      move(y+1, x);
      attron(COLOR_PAIR(2));
      printw("Jouer!!");
      move(y+3, x);
      attron(COLOR_PAIR(1));
      printw("Quitter");
      break;
      ;;
  }
}

//si la tete du serpent est sur un fruit, on le fait disparaitre et on en genere un nouveau
int serpentMangeFruit(grille * g, serpent * serp){
  if (g->fruit.x == serp->tete_serpent.y && g->fruit.y == serp->tete_serpent.x){
    g->fruit.x = -1;
    g->fruit.y = -1;
    grilleTirageFruit(g);
    return 1;     
  }
  return 0;
}
