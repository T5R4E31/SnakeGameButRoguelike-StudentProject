#ifndef GRILLE_H_
#define GRILLE_H_

#include "pos.h"
typedef struct grille {
  int n;
  int m;
  char *** grid;
  pos fruit;
} grille;

grille * grilleAllouer(int n, int m);
void grilleVider(grille * g);
void grilleTirageFruit(grille * g);
void grilleRemplir(grille * g);
void grilleDesallouer(grille * g);
void grilleRedessiner(grille * g);


#endif 
