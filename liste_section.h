#ifndef _LISTE_SECTION_H
#define _LISTE_SECTION_H

#include <stdio.h>
#include "pos.h"
//chaque section a une taille et une couleur
//stockee en int
typedef struct section {
  int taille;
  int color;
  pos pos_section;
} section;

//declaration de liste chainee clasique
typedef struct listSection {
  section sec;
  struct listSection * next;
} listSection;


section * creerSection(int taille, int color, pos pos);
void desallouerSection(section * sec);
void ajouterSectionTete(listSection * l, section * sec);
listSection * creerListSection();
void ajouterSectionQueue(listSection * l, section * sec);
void desallouerListSection(listSection * l);
listSection * dernierListSection(listSection * l);
listSection * avantDernierListSection(listSection * l);

#endif
