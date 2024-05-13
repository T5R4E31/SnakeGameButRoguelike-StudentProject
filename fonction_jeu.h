#ifndef _FONCTION_JEU_H
#define _FONCTION_JEU_H
#include "grille.h"
#include "objet.h"

int gameLoopSnake(grille * g, int mult_fruit, int add_fruit, int objective, listObjet * itemPlayer);
void printGameMenu(int opt);
int serpentMangeFruit(grille * g, serpent * serp);
void gameMain(grille * g);

#endif
