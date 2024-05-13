#include "fonction_jeu.h"
#include "grille.h"
#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAX_WAVE 5

int gameLoopSnake(grille * g, int mult_fruit, int add_fruit, int objective, listObjet * itemPlayer){
  int input = -1;
  int last_input = 'f';
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
  grilleMurer(g, 1);
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
        if (last_input == 's'){
          last_input = 's';
          input = 's';
          continue;
        }
        --player->tete_serpent.x;
        last_input = input;
        ajouterSectionTete(player->head, creerSection(1, 45, player->tete_serpent));
        if (serpentMangeFruit(g, player)){
          score += (add_fruit + 1) * mult_fruit;
          continue;
        }
        tmp = dernierListSection(player->head);
        avantDernierListSection(player->head)->next = NULL;
        desallouerListSection(tmp);
        break;
      case 's':
        if (last_input == 'z'){
          last_input = 'z';
          input = 'z';
          continue;
        }
        ++player->tete_serpent.x;
        last_input = input;
        ajouterSectionTete(player->head, creerSection(1, 45, player->tete_serpent));
        if (serpentMangeFruit(g, player)){ 
          score += (add_fruit + 1) * mult_fruit;
          break;
        }
        tmp = dernierListSection(player->head);
        avantDernierListSection(player->head)->next = NULL;
        desallouerListSection(tmp);
        break;
      case 'd':
        if (last_input == 'q'){
          last_input = 'q';
          input = 'q';
          continue;
        }
        ++player->tete_serpent.y;
        last_input = input;
        ajouterSectionTete(player->head, creerSection(1, 45, player->tete_serpent));
        if (serpentMangeFruit(g, player)){
          score += (add_fruit + 1) * mult_fruit;
          break;
        }
        tmp = dernierListSection(player->head);
        avantDernierListSection(player->head)->next = NULL;
        desallouerListSection(tmp);
        break;
      case 'q':
        if (last_input == 'd'){
          last_input = 'd';
          input = 'd';
          continue;
        }
        --player->tete_serpent.y;
        last_input = input;
        ajouterSectionTete(player->head, creerSection(1, 45, player->tete_serpent));
        if (serpentMangeFruit(g, player)){
          score += (add_fruit + 1) * mult_fruit; 
          break;
        }
        tmp = dernierListSection(player->head);
        avantDernierListSection(player->head)->next = NULL;
        desallouerListSection(tmp);
        break;
      //touche p pour quitter
      //a rajouter : menu pour les information de gameplay
      case 'p':
        return 1;
        break;
      default:
        if (last_input == 'f'){
          input = getch();
          grilleRemplir(g, player);
          grilleRedessiner(g);
          continue;
        }
        input = last_input;
        continue;
    }
    
    input = getch();


    //si le joueur touche un mur, on retourne a l'ecran titre (sans ca le programme segfault)
    if (player->tete_serpent.x == -1 || player->tete_serpent.y == 0 || player->tete_serpent.x == g->n || player->tete_serpent.y == g->m-1){
      desallouerListSection(player->head);
      player->head = NULL;
      free(player);
      return 1;
    }
    
    //si le joueur se touche, on retourne a l'ecran titre
    if (!strcmp(g->grid[player->tete_serpent.x][player->tete_serpent.y], "serp")){
      desallouerListSection(player->head);
      player->head = NULL;
      free(player);
      return 1;
    }

    if (!strcmp(g->grid[player->tete_serpent.x][player->tete_serpent.y], "w")){
      desallouerListSection(player->head);
      player->head = NULL;
      free(player);
      return 1;
    }

    
    //on vide dans un premier temps la grille pour eviter les traces de serpent
    grilleVider(g);


    //met le nouveau serpent dans la grille et l'affiche
    grilleRemplir(g, player);
    grilleRedessiner(g);

    printListObjet(itemPlayer);
    printw("Votre score : %d  ", score);
    printw("Objectif de cette manche : %d", objective);

    if (score >= objective){
      desallouerListSection(player->head);
      player->head = NULL;
      free(player);
      return 0;
    }
    //fflush() s'assure de bien afficher tout ce qu'il y a dans le cache
    fflush(stdout);

  }

  free(player);
  return 1;
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
  move(y+2, x - 44/2);
  printw("Utilisez 'z' et 's' pour choisir une option!");
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

void gameMain(grille * g){ 
  int mult_fruit = 1;
  int add_fruit = 0;
  int objective = 10;
  
  listObjet * itemPlayer = creerListObjet(serpentPeluche(initObjet()));
  ajouterObjet(itemPlayer, pomme(initObjet()));


  for (int i = 1; i<=MAX_WAVE; i++){
    clear();
    move(getmaxy(stdscr)/2, getmaxx(stdscr)/2);
    printw("MANCHE %d/%d", i, MAX_WAVE);
    refresh();
    sleep(2);
    if (gameLoopSnake(g, mult_fruit, add_fruit, objective, itemPlayer)){
      clear();
      move(getmaxy(stdscr)/2, getmaxx(stdscr)/2);
      printw("VOUS AVEZ PERDU BOUUUUUH");
      refresh();
      sleep(2);
      return;
    }
    objective += objective * 1.5 + 4;
    grilleVoid(g);
  }
  if (gameLoopSnake(g, mult_fruit, add_fruit, objective, itemPlayer)){
    return;
  }
  return;
}
