#include <stdlib.h>
#include "liste_section.h"

//creer la donnee "section", en malloc
section * creerSection(int taille, int color){
  section * res = malloc(sizeof(section));
  res->taille = taille;
  res->color = color;
  return res;
}

//libere la donnee section
void desallouerSection(section * sec){
  if (sec == NULL) return;
  free(sec);
  return;
}

//cree une liste section vide
listSection * creerListSection(){
  listSection * res = malloc(sizeof(listSection));
  res->sec = *(creerSection(0, 0));
  res->next = NULL;
  return res;
}

//ajoute a la tete d'une liste une section, cree une nouvelle liste au debut
//on doit l'utiliser comme : ajouterSectionTete(serpent->head, section_a_ajouter)
//complexite o(1)
void ajouterSectionTete(listSection * l, section * sec){
  listSection * temp = creerListSection();
  temp->sec = *(sec);
  temp->next = l->next;
  l->next = temp;
  return;
}

//ajoute a la queue d'une liste une section
//a note que la structure serpent ne contenant pas la queue de la liste, il faut la parcourir
//complexite de o(n)
void ajouterSectionQueue(listSection * l, section * sec){
  if (l->next == NULL){
    l->next = creerListSection();
    l->next->sec = *sec;
    l->next->next = NULL;
    return;
  }
  ajouterSectionQueue(l->next, sec);
  return;
}

void desallouerListSection(listSection * l){
  if (l->next == NULL){
    free(l);
    return;
  }
  desallouerListSection(l);
  free(l);
  return;
}

