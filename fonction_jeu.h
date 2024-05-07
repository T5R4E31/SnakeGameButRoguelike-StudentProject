#ifndef _FONCTION_JEU_H
#define _FONCTION_JEU_H
#include "grille.h"

void gameLoopSnake(grille * g);
void printGameMenu(int opt);
int serpentMangeFruit(grille * g, serpent * serp);

#endif
