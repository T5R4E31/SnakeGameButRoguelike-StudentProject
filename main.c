#include <stdio.h>
#include <stdlib.h>

#include "grille.h"

int main(){
  grille * toto = grilleAllouer(20, 30);
  grilleVider(toto); 
  grilleTirageFruit(toto);

  serpent * tata = malloc(sizeof(serpent));
  tata->tete_serpent.x = 3;
  tata->tete_serpent.y = 4;
  printf("test 1\n");
  tata->head = creerListSection();
  printf("test 2\n");
  ajouterSectionTete(tata->head, creerSection(5, 44));
  printf("test 3\n");
  ajouterSectionTete(tata->head, creerSection(3, 47));
  printf("test 4\n");
  grilleRemplir(toto, tata);
  printf("test 5\n");
  grilleRedessiner(toto);
  printf("test 6\n");

  return EXIT_SUCCESS;
}
