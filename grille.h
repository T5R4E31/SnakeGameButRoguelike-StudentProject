#ifndef GRILLE_H_
#define GRILLE_H_

#include "pos.h"
#include "serpent.h"
typedef struct grille {
  int n;
  int m;
  char *** grid;
  pos fruit;
} grille;

grille * grilleAllouer(int n, int m);
void grilleVider(grille * g);
void grilleVoid(grille * g);
int minTailleGrille(grille * g);
void grilleTirageFruit(grille * g);
int estFruitGrille(grille * g);
void grilleRemplir(grille * g, serpent * serp);
void grilleDesallouer(grille * g);
void grilleRedessiner(grille * g);
void grilleMurer(grille * g, int lvl, int less_wall);

#endif 
