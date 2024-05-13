#include "objet.h"
#include <string.h>
#include <ncurses.h>

objet * initObjet(){
  objet * temp = malloc(sizeof(objet));
  temp->nom = malloc(sizeof(char)*30);
  temp->descr = malloc(sizeof(char)*200);
  return temp;
}

objet * serpentPeluche(objet * obj){
  obj->nom = "Serpent en Peluche";
  obj->descr = "+1.2 au multiplicateur de score par fruit";
  return obj;
}

objet * pomme(objet * obj){
  obj->nom = "Pomme";
  obj->descr = "+1 vie, si le serpent meure, la vague recommence";
  return obj;
}

objet * caillou(objet * obj){
  obj->nom = "Caillou";
  obj->descr = "Moins de mur à la prochaine vague, détruit à la prochaine vague";
  return obj;
}

listObjet * creerListObjet(objet * obj){
  listObjet * temp = malloc(sizeof(listObjet));
  temp->obj = obj;
  temp->prochain_objet = NULL;
  return temp;
}

void ajouterObjet(listObjet * l, objet * obj){
  listObjet * tmp = l;
  while (tmp->prochain_objet != NULL){
    tmp = tmp->prochain_objet;
  }
  tmp->prochain_objet = creerListObjet(obj);
}

int posObjet(listObjet * l, objet * obj){
  int i = 0;
  listObjet * tmp = l;
  while (tmp != NULL){
    if (!strcmp(tmp->obj->nom, obj->nom)){
      return i;
    }
    i++;
    tmp = tmp->prochain_objet;
  }
  return -1;
}

void supprimerPosObjet(listObjet * l, int pos){
  listObjet * tmp = l;
  for (int i = 0; i<pos-1; i++){
    if (tmp == NULL){
      return;
    }
    tmp = tmp->prochain_objet;
  }

  listObjet * avant = tmp;
  if (tmp->prochain_objet == NULL){
    return;
  }
  
  if (tmp->prochain_objet->prochain_objet == NULL){
    free(tmp->prochain_objet);
    tmp->prochain_objet = NULL;
    return;
  }
  listObjet * current = tmp->prochain_objet;
  listObjet * suivant = current->prochain_objet;
  free(current);
  avant->prochain_objet = suivant;
  return;
}

void printListObjet(listObjet * l){
  int x = 10;
  int y = 20;
  listObjet * tmp = l;
  move(y, x);
  while (tmp!=NULL){
    move(++y, x);
    printw(tmp->obj->nom);
    tmp = tmp->prochain_objet;
  }
  return;
}
