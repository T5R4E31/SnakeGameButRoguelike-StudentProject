#include <stdio.h>
#include <stdlib.h>

#include "grille.h"

int main(){
  grille * toto = grilleAllouer(4, 6);
  grilleVider(toto);
  grilleTirageFruit(toto);
  return EXIT_SUCCESS;
}
