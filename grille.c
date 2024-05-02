#include "grille.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>

//Alloue une grille de taille n m.
//Allouer en malloc(n*m*12*sizeof(char)) fait bugger le programme donc retire
//complexite similaire a la fonction grilleRedessiner()
grille * grilleAllouer(int n, int m){
  grille * res = malloc(sizeof(grille));
  res->n = n;
  res->m = m;
  res->grid = malloc(n*sizeof(char**));
  for (int j = 0; j < n; j++){
    res->grid[j] = malloc(m*sizeof(char*));
  }
  for (int i = 0; i < n; i++){
    for (int j = 0; j < m; j++){
      res->grid[i][j] = malloc(12*sizeof(char));
    }
  }
  res->fruit.x = -1;
  res->fruit.y = -1;
  return res;
}

//Rempli la grille d'espace fond noir.
void grilleVider(grille * g){
  int i, j;
  if (g == NULL) return;
  for (i = 0; i<g->n; i++){
    for (j = 0; j<g->m; j++){
      if (!(strcmp(g->grid[i][j], "f"))){
        continue;
      }
      (g->grid)[i][j]= " ";
    }
  }
  return;
}

//Tire un fruit aléatoire avec rand() et le place dans la grille.
//on le localise avec "f" pour plus de simplicite
void grilleTirageFruit(grille * g){
  if (g==NULL) return;
  srand(time(NULL));
  int pos_x = rand() % g->n;
  int pos_y = rand() % g->m;
  g->fruit.x = pos_y;
  g->fruit.y = pos_x;
  g->grid[pos_x][pos_y] = "f";
  return;
}

//Met le serpent dans la grille, pour l'instant uniquement horizontalement.
//on stock la donnee serpent a l'aide d'un string
//La suite sera dans le prochain commit
void grilleRemplir(grille * g, serpent * serp){
  listSection * head = serp->head;
  int x = serp->tete_serpent.x;
  int y = serp->tete_serpent.y;
  while (head != NULL){
    for (int i = 0; i<head->sec.taille; i++){
      (g->grid)[x][++y] = "serp";
    }
    head = head->next;
  }
  return;
}

//Libere une grille
void grilleDesallouer(grille * g){
  if (g == NULL) return;
  free(g->grid);
  return;
}

//Affiche entièrement la grille.
//Les couleurs ont été choisi par souci d'esthétique
//On affiche d'abord la premiere ligne, puis le tableau, puis la derniere ligne
//La fonction affiche les couleurs à l'aide de ncurses, et non de caractere d'echappement
void grilleRedessiner(grille * g){
  clear();
  //On calcul l'endroit où positionner le curseur pour que ce soit centre
  int x, y;
  x = getmaxx(stdscr)/2 - g->m;
  y = getmaxy(stdscr)/2 - g->n/2;
  move(y, x);
  //premiere ligne
  for (int i = 0; i<g->m; i++){
    attron(COLOR_PAIR(4));
    printw("  ");
  }

  y++;
  //corps
  for (int i = 0; i<g->n; i++){
    //mur de gauche
    move(y+i, x);
    attron(COLOR_PAIR(4));
    printw("  ");
    for (int j = 0; j<g->m; j++){
      //comme on possede un controle precis du curseur, on n'affiche que les endroits utile (fruits et serpent)
      //en evitant des acces memoires inutiles
      if (!strcmp(g->grid[i][j], "f")){
        move(y+i, x+2*j);
        attron(COLOR_PAIR(5));
        printw("  ");
        continue;
      }
      if (!strcmp(g->grid[i][j], "serp")){
        move(y+i, x+2*j);
        attron(COLOR_PAIR(4));
        printw("  ");
        continue;
      }
    }
    //mur de droite
    move(y+i, x+2*(g->m-1));
    attron(COLOR_PAIR(4));
    printw("  ");
    //on s'assure que tout soit bien affiche
  }
  //on se met a la fin de ce qui est affiche et on affiche la derniere ligne
  y+=g->n;
  move(y, x);
  attron(COLOR_PAIR(4));
  for (int i = 0; i<g->m; i++){
    printw("  ");
  }
  attron(COLOR_PAIR(2));
  move(y+1, x);
}

//Fonction cree pour simplifier le code de la fonction ci dessus. 
//Revoie un tableau correspondant à la couleur.
//A note que switch() est utilise ici car sa complexite est strictement de 1
//contrairement a if, qui aura une complexite augmentant lineairement par rapport au 
//nombre de if enchaine
char * setColor(int color){
  char * s = malloc(10*sizeof(char));
  switch (color){
    case 40:
      s = "\e[40m ";
      return s;
    case 41:
      s = "\e[41m ";
      return s;
    case 42:
      s = "\e[42m ";
      return s;
    case 43:
      s = "\e[43m ";
      return s;
    case 44:
      s = "\e[44m ";
      return s;
    case 45:
      s = "\e[45m ";
      return s;
    case 46:
      s = "\e[46m ";
      return s;
    case 47:
      s = "\e[47m ";
      return s;
    case 48:
      s = "\e[48m ";
      return s;
    case 49:
      s = "\e[49m ";
      return s;
    default:
      return NULL;
  }
}
