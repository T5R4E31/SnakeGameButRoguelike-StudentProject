#include <stdio.h>
#include <stdlib.h>

typedef struct objet {
  char * nom;
  char * descr;
} objet;

typedef struct listObjet {
  objet * obj;
  struct listObjet * prochain_objet;
} listObjet;

objet * initObjet();
objet * serpentPeluche(objet * obj);
objet * pomme(objet * obj);
objet * caillou(objet * obj);

listObjet * creerListObjet(objet * obj);
void ajouterObjet(listObjet * l, objet * obj);
void supprimerObjetPos(listObjet * l, int pos);
int posObjet(listObjet * l, objet * obj);
void printListObjet(listObjet * l);
