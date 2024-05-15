#include <stdlib.h>
#include "liste_section.h"

//creer la donnee "section", en malloc
section * creerSection(int taille, int color, pos pos){
  section * res = malloc(sizeof(section));
  res->taille = taille;
  res->color = color;
  res->pos_section.x = pos.x;
  res->pos_section.y = pos.y;
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
  pos tmp;
  tmp.x = 0;
  tmp.y = 0;
  res->sec = *(creerSection(0, 0, tmp));
  res->next = NULL;
  return res;
}

//ajoute a la tete d'une liste une section, cree une nouvelle liste au debut
//on doit l'utiliser comme : ajouterSectionTete(serpent->head, section_a_ajouter)
//complexite o(1)
void ajouterSectionTete(listSection * l, section * sec){
  listSection * temp = malloc(sizeof(listSection));
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

//afin de desallouer la liste section
void desallouerListSection(listSection * l){
  if (l == NULL) return;
  listSection * tmp = l;
  listSection * current_l = tmp;
  while (current_l!=NULL){
    tmp = tmp->next;
    free(current_l);
    current_l = tmp;
  }
}


//on veut obtenir la fin de la liste section, on utilise un while pour cela
//(on ne stock pas la queue du serpent, on des raisons de lisibilite du code)
listSection * dernierListSection(listSection * l){
  if (l == NULL) return NULL;
  listSection * tmp = l;
  while (tmp->next!=NULL){
    tmp = tmp->next;
  }
  return tmp;
}

//dans certain cas, il sera utile d'arriver a l'avant dernier maillon de la chaine
listSection * avantDernierListSection(listSection * l){
  if (l == NULL) return NULL;
  if (l->next == NULL) return NULL;
  listSection * tmp = l;
  while (tmp->next->next != NULL){
    tmp = tmp->next;
  }
  return tmp;
}
