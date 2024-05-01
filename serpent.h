#ifndef _SERPENT_H
#define _SERPENT_H

#include "pos.h"
#include "liste_section.h"

//La structure serpent contient la tete du serpent en position (pos)
//et l'adresse de sa tete comme liste chainee
typedef struct serpent {
  pos tete_serpent;
  listSection * head;
} serpent;

#endif
