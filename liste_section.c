#include <stdlib.h>
#include "liste_section.h"

section * creerSection(int taille, int color){
  section * res = malloc(sizeof(section));
  res->taille = taille;
  res->color = color;
  return res;
}

void desallouerSection(section * sec){
  if (sec == NULL) return;
  free(sec);
  return;
}

listSection * creerListSection(){
  listSection * res = malloc(sizeof(listSection));
  res->sec = *(creerSection(0, 0));
  res->next = NULL;
  return res;
}

void ajouterSectionTete(listSection * l, section * sec){
  listSection * temp = creerListSection();
  temp->sec = *(sec);
  temp->next = l->next;
  l->next = temp;
  return;
}

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

