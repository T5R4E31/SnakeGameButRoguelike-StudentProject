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
objet * helium(objet * obj);
objet * caillou(objet * obj);
objet * ticketLoterie(objet * obj);
objet * paquetChips(objet * obj);
objet * calculatrice(objet * obj);

listObjet * creerListObjet(objet * obj);
void ajouterObjet(listObjet * l, objet * obj);
void supprimerPosObjet(listObjet * l, int pos);
objet * retourneObjet(listObjet * l, int pos);
int posObjet(listObjet * l, objet * obj);
void printListObjet(listObjet * l, int x, int y);
int objCount(listObjet * l, objet * obj);
int listSize(listObjet * l);
void detruireListObjet(listObjet * l);
