#include "grille.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
      (g->grid)[i][j]= "\33[0m ";
    }
  }
  return;
}

//Tire un fruit aléatoire avec rand() et le place dans la grille.
void grilleTirageFruit(grille * g){
  if (g==NULL) return;
  srand(time(NULL));
  int pos_x = rand() % g->n;
  int pos_y = rand() % g->m;
  g->fruit.x = pos_y;
  g->fruit.y = pos_x;
  g->grid[pos_x][pos_y] = "\e[39;42m ";
  return;
}

//Met le serpent dans la grille, pour l'instant uniquement horizontalement.
//La suite sera dans le prochain commit
void grilleRemplir(grille * g, serpent * serp){
  listSection * head = serp->head;
  int x = serp->tete_serpent.x;
  int y = serp->tete_serpent.y;
  while (head != NULL){
    for (int i = 0; i<head->sec.taille; i++){
      (g->grid)[x][++y] = setColor(head->sec.color);
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
//complexite quadratique, meme si on n'utilise pas une matrice carree, donc pas tout à fait.
//o(n^2) si on considère qu'on augmente n et m simultanément
//o(n) si on fixe une des deux taille
void grilleRedessiner(grille * g){
  printf("\33[2J");
  printf("\33[H"); 
  for (int i = 0; i<g->m+2; i++){
    printf("\e[39;45m  ");
  }
  printf("\e[0m ");
  printf("\33[1E");
  for (int i = 0; i<g->n; i++){
    printf("\e[39;45m  ");
    for (int j = 0; j<g->m; j++){
      printf("%s", g->grid[i][j]);
      printf("%s", g->grid[i][j]);
    }
    printf("\e[39;45m  \e[0m \33[1E");
  }

  for (int i = 0; i<g->m+2; i++){
    printf("\e[39;45m  ");
  }
  printf("\e[0m \33[1E");
  fflush(0);
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
