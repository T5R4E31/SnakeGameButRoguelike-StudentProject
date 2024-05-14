#ifndef _FONCTION_JEU_H
#define _FONCTION_JEU_H
#include "grille.h"
#include "objet.h"

int gameLoopSnake(grille * g, int mult_fruit, int add_fruit, int objective, listObjet * itemPlayer, int lvl, int less_wall, int intangible);
void printGameMenu(int opt);
int serpentMangeFruit(grille * g, serpent * serp);
void gameMain(grille * g, int mode_infini);
void printObj(objet * obj, int x, int y);
objet * menuChoixObj(listObjet * repertoire);
int menuChoixModeInfini(listObjet * itemPlayer);

#endif
