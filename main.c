#include <stdio.h>
#include <stdlib.h>

#include "grille.h"

int main(){
  printf("test 1");
  grille * toto = grilleAllouer(4, 6);
  printf("test 2");
  grilleVider(toto);
  printf("test 3");
  grilleTirageFruit(toto);
  return EXIT_SUCCESS;
}
