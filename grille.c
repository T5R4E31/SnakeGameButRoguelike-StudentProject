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
    fflush(0);
    for (j = 0; j<g->m; j++){
      fflush(0);
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

void grilleRemplir(grille * g){
  int i, j;
  if (g == NULL) return;
  for (i = 0; i<g->n; i++){
    for (j = 0; j<g->m; j++){
      strcpy(g->grid[i][j], "\e[48;5;0m ");
    }
  }
  return;
}

void grilleDesallouer(grille * g){
  if (g == NULL) return;
  free(g->grid);
  return;
}

void grilleRedessiner(grille * g){
  for (int i = 0; i<g->m+2; i++){
    printf("\e[39;45m  ");
  }
  printf("\n");
  for (int i = 0; i<g->n; i++){
    printf("\e[39;45m  ");
    for (int j = 0; j<g->m; j++){
      printf("%s", g->grid[i][j]);
      printf("%s", g->grid[i][j]);
    }
    printf("\e[39;45m  \n");
  }

  for (int i = 0; i<g->m+2; i++){
    printf("\e[39;45m  ");
  }
}
