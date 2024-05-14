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
      if (!(strcmp(g->grid[i][j], "w"))){
        continue;
      }
      (g->grid)[i][j]= " ";
    }
  }
  return;
}

void grilleVoid(grille * g){
  int i, j;
  if (g == NULL) return;
  for (i = 0; i<g->n; i++){
    for (j = 0; j<g->m; j++){
      (g->grid)[i][j] = " ";
    }
  }
}

int minTailleGrille(grille * g){
  if (g->m<g->n) return g->m;
  return g->n;
} 

//Tire un fruit aléatoire avec rand() et le place dans la grille.
//on le localise avec "f" pour plus de simplicite
//les calculs effectuer on pour but d'eviter de generer un fruit dans le joueur ou dans un mur
void grilleTirageFruit(grille * g){
  if (g==NULL) return;
  srand(time(NULL));
  int min_pos = minTailleGrille(g);
  int pos_x = 2 + rand() % (min_pos-3);
  int pos_y = 2 + rand() % (min_pos-3);
  while (!(strcmp(g->grid[pos_x][pos_y], "serp")) || !(strcmp(g->grid[pos_x][pos_y], "w"))){
    pos_x = 2 + rand() %(g->n-3);
    pos_y = 2 + rand() % (g->m-3);
  }
  g->fruit.x = pos_y;
  g->fruit.y = pos_x;
  g->grid[pos_x][pos_y] = "f";
  return;
}

//savoir si un fruit est dans la grille
//cela pourra etre utile dans des futures fonctionalites
int estFruitGrille(grille * g){
  for (int i = 0; i<g->n; i++){
    for (int j = 0; j<g->m; j++){
      if (strcmp(g->grid[i][j], "f") == 0){
        return 1;
      }
    }
  }
  return 0;
}

//Met le serpent dans la grille, pour l'instant uniquement horizontalement.
//on stock la donnee serpent a l'aide d'un string
//La suite sera dans le prochain commit
void grilleRemplir(grille * g, serpent * serp){
  listSection * head = serp->head;
  while (head != NULL){
    for (int i = 0; i<head->sec.taille; i++){
      (g->grid)[head->sec.pos_section.x][head->sec.pos_section.y] = "serp";
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
  int color = 8;
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
        attron(COLOR_PAIR(5));
        continue;
      }
      if (!strcmp(g->grid[i][j], "serp")){
        move(y+i, x+2*j);
        attron(COLOR_PAIR(color));
        printw("  ");
        attron(COLOR_PAIR(5));
        continue;
      }
      if (!strcmp(g->grid[i][j], "w")){
        move(y+i, x+2*j);
        attron(COLOR_PAIR(4));
        printw("  ");
        attron(COLOR_PAIR(5));
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


void grilleMurer(grille * g, int lvl, int less_wall){
  if (g == NULL) return;
  float wall_coef = less_wall == 1 ? 0.2 : 1;
  srand(time(NULL));
  for (int i = 0; i<g->n; i++){
    for (int j = 0; j<g->m; j++){
      if (rand() % 100 <= (lvl*1.05 + 1)*wall_coef && (strcmp(g->grid[i][j], "serp") != 0)){ 
        g->grid[i][j] = "w";
      }
    }
  }
  return;
}
