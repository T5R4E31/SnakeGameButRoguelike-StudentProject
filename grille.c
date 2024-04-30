#include "grille.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


grille * grilleAllouer(int n, int m){
  grille * res = malloc(sizeof(grille));
  res->n = n;
  res->m = m;
  res->grid = malloc(n*m*12*sizeof(char));
  res->fruit.x = -1;
  res->fruit.y = -1;
  return res;
}

void grilleVider(grille * g){
  int i, j;
  if (g == NULL) return;
  for (i = 0; i<g->n; i++){
    for (j = 0; i<g->m; i++){
      strcpy(g->grid[i][j], "\\33[0m ");
    }
  }
  return;
}

void grilleTirageFruit(grille * g){
  if (g==NULL) return;
  srand(time(NULL));
  int pos_x = rand() % g->n;
  int pos_y = rand() % g->m;
  g->fruit.x = pos_x;
  g->fruit.y = pos_y;
  return;
}

void grilleRemplir(grille * g){
  int i, j;
  if (g == NULL) return;
  for (i = 0; i<g->n; i++){
    for (j = 0; i<g->m; i++){
      strcpy(g->grid[i][j], "\\33[41m ");
    }
  }
  return;
}

void grilleDesallouer(grille * g){
  if (g == NULL) return;
  free(g->grid);
  return;
}
