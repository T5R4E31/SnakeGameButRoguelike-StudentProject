
typedef struct section {
  int taille;
  char * color;
} section;

typedef struct listSection {
  section sec;
  struct listSection * next;
} listSection;
