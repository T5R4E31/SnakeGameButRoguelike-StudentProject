#include "objet.h"
#include <string.h>
#include <ncurses.h>

//initialise une structure objet
objet * initObjet(){
  objet * temp = malloc(sizeof(objet));
  temp->nom = malloc(sizeof(char)*30);
  temp->descr = malloc(sizeof(char)*200);
  return temp;
}

//toute les fonctions suivante initialise les objets differents
objet * serpentPeluche(objet * obj){
  obj->nom = "Serpent en Peluche";
  obj->descr = "+2 au multiplicateur de score par fruit";
  return obj;
}

objet * pomme(objet * obj){
  obj->nom = "Pomme";
  obj->descr = "+1 vie, si le serpent meure, la vague recommence, détruit à l'achat";
  return obj;
}

objet * helium(objet * obj){
  obj->nom = "Bouteille d'hélium rigolote";
  obj->descr = "Passe à travers les murs internes à la prochaine vague, détruit à l'achat";
  return obj;
}

objet * caillou(objet * obj){
  obj->nom = "Caillou";
  obj->descr = "Moins de mur pour la prochaine vague, détruit à l'achat";
  return obj;
}

objet * ticketLoterie(objet * obj){
  obj->nom = "Ticket de Loterie";
  obj->descr = "1 chance sur 2 de passer la prochaine vague, détruit à l'achat";
  return obj;
}

objet * paquetChips(objet * obj){
  obj->nom = "Paquet de Chips";
  obj->descr = "+3 au score à chaque fruit";
  return obj;
}

objet * calculatrice(objet * obj){
  obj->nom = "Calculatrice";
  obj->descr = "L'objectif de score diminue";
  return obj;
}

//la plupart des prochaines fonctions sont semblables à celle de liste_section.h
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

//donne la position d'un objet dans la liste
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

//supprime un objet de la liste par la technique de la sentinel
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

//retourne un objet à la position pos
objet * retourneObjet(listObjet * l, int pos){
  listObjet * tmp = l;
  for (int i = 0; i<pos; i++){
    if (l==NULL){
      return initObjet();
    }
    tmp = tmp->prochain_objet;
  }
  return tmp->obj;
}

//affiche la listObjet à la position x y
void printListObjet(listObjet * l, int x, int y){
  listObjet * tmp = l;
  move(y, x);
  while (tmp!=NULL){
    y+=2;
    move(y, x);
    printw(tmp->obj->nom);
    tmp = tmp->prochain_objet;
  }
  return;
}

//compte le nombre d'un objet
int objCount(listObjet * l, objet * obj){
  listObjet * temp = l;
  int i = 0;
  while (temp!=NULL){
    if (!strcmp(temp->obj->nom, obj->nom)){
      i++;
    }
    temp = temp->prochain_objet;
  }
  return i;
}

//renvoie la taille de la liste
int listSize(listObjet * l){
  listObjet * temp = l;
  int i = 0;
  while (temp!=NULL){
    temp = temp->prochain_objet;
    i++;
  }
  return i;
}

//libere la listObjet
void detruireListObjet(listObjet * l){
  if (l == NULL) return;
  listObjet * tmp = l;
  listObjet * current_l = tmp;
  while (current_l!=NULL){
    if (current_l->obj != NULL){
      free(current_l->obj);
    }
    tmp = tmp->prochain_objet;
    free(current_l);
    current_l = tmp;
  }
  return;
}
