#include <stdio.h>

typedef struct section {
  int taille;
  int color;
} section;

typedef struct listSection {
  section sec;
  struct listSection * next;
} listSection;


section * creerSection(int taille, int color);
void desallouerSection(section * sec);
void ajouterSectionTete(listSection * l, section * sec);
listSection * creerListSection();
void ajouterSectionQueue(listSection * l, section * sec);
void desallouerListSection(listSection * l);

