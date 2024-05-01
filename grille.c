#include "grille.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


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

void grilleDesallouer(grille * g){
  if (g == NULL) return;
  free(g->grid);
  return;
}

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
