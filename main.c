#include <stdio.h>
#include <stdlib.h>

#include "grille.h"
#include "serpent.h"
#include "liste_section.h"

int main(){
  grille * toto = grilleAllouer(20, 30);
  grilleVider(toto); 
  grilleTirageFruit(toto);
  grilleRedessiner(toto);
  return EXIT_SUCCESS;
}
