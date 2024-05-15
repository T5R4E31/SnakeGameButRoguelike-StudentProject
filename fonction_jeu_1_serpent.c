#include "fonction_jeu.h"
#include "grille.h"
#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

#define MAX_WAVE 5
#define POS_SERP_PEL 0
#define POS_POM 1 
#define POS_HELIUM 2
#define POS_CAILLOU 3
#define POS_TICKET 4
#define POS_CHIPS 5
#define POS_CALC 6

#define DELAY 1

int gameLoopSnake(grille * g, int mult_fruit, int add_fruit, int objective, listObjet * itemPlayer, int lvl, int less_wall, int intangible){
  int input = -1;
  int last_input = 'f';
  int score = 0;
  listSection * tmp = malloc(sizeof(listSection));
  struct timeval start;
  struct timeval stop;
  
  //creation d'un serpent avec une position et une couleur arbitraire
  //a rajouter : position aleatoire et couleur aleatoire
  serpent * player = malloc(sizeof(serpent));
  player->head = creerListSection();
  player->tete_serpent.x = 1;
  player->tete_serpent.y = 2;
  ajouterSectionTete(player->head, creerSection(1, 45, player->tete_serpent));

  //on s'assure de vider la grille
  grilleVoid(g);

  //cinematique de demarrage
  grilleRedessiner(g);
  refresh();
  usleep(500*1000);
  printListObjet(itemPlayer, 4*getmaxx(stdscr)/5, getmaxy(stdscr)/4);
  refresh();
  usleep(300*1000);
  move(30, 20);
  printw("Votre score : %d  ", score);
  refresh();
  usleep(300*1000);
  move(32, 20);
  printw("Objectif de cette manche : %d", objective);
  refresh();
  usleep(300*1000);

  //on re rempli la grille avec notre serpent actuel
  grilleRemplir(g, player);
  //on effectue le tirage pour le premier fruit
  grilleMurer(g, lvl, less_wall);
  grilleTirageFruit(g);
  while (input!='#'){
    //on prend l'input clavier de l'utilisateur
    printListObjet(itemPlayer, 4*getmaxx(stdscr)/5, getmaxy(stdscr)/4);
    move(30, 20);
    printw("Votre score : %d  ", score);
    move(32, 20);
    printw("Objectif de cette manche : %d", objective);

    switch (input){
      //deplacement de base de tout jeu video
      //on deplace la tete du serpent en fonction des entrees joueurs
      //a chaque tour, on fait disparaitre la queue et on rajoute une case à la tete,
      //afin de deplacer d'une case le serpent
      //si on a mange un fruit, on ne fait pas disparaitre la derniere case 
      //on fait cela pour chaque input possible

      case 'z':
        if (last_input == 's'){
          last_input = 's';
          input = 's';
          continue;
        }
        --player->tete_serpent.x;
        last_input = input;
        ajouterSectionTete(player->head, creerSection(1, 45, player->tete_serpent));
        if (serpentMangeFruit(g, player)){
          score += (add_fruit + 1 + score/10) * mult_fruit;
          continue;
        }
        tmp = dernierListSection(player->head);
        avantDernierListSection(player->head)->next = NULL;
        desallouerListSection(tmp);
        break;
      case 's':
        if (last_input == 'z'){
          last_input = 'z';
          input = 'z';
          continue;
        }
        ++player->tete_serpent.x;
        last_input = input;
        ajouterSectionTete(player->head, creerSection(1, 45, player->tete_serpent));
        if (serpentMangeFruit(g, player)){ 
          score += (add_fruit + 1 + score/10) * mult_fruit;
          break;
        }
        tmp = dernierListSection(player->head);
        avantDernierListSection(player->head)->next = NULL;
        desallouerListSection(tmp);
        break;
      case 'd':
        if (last_input == 'q'){
          last_input = 'q';
          input = 'q';
          continue;
        }
        ++player->tete_serpent.y;
        last_input = input;
        ajouterSectionTete(player->head, creerSection(1, 45, player->tete_serpent));
        if (serpentMangeFruit(g, player)){
          score += (add_fruit + 1 + score/10) * mult_fruit;
          break;
        }
        tmp = dernierListSection(player->head);
        avantDernierListSection(player->head)->next = NULL;
        desallouerListSection(tmp);
        break;
      case 'q':
        if (last_input == 'd'){
          last_input = 'd';
          input = 'd';
          continue;
        }
        --player->tete_serpent.y;
        last_input = input;
        ajouterSectionTete(player->head, creerSection(1, 45, player->tete_serpent));
        if (serpentMangeFruit(g, player)){
          score += (add_fruit + 1 + score/10) * mult_fruit; 
          break;
        }
        tmp = dernierListSection(player->head);
        avantDernierListSection(player->head)->next = NULL;
        desallouerListSection(tmp);
        break;
      //touche p pour quitter
      //a rajouter : menu pour les information de gameplay
      case 'p':
        return 2;
        break;
      default:
        if (last_input == 'f'){
          input = getch();
          grilleRemplir(g, player);
          grilleRedessiner(g);
          continue;
        }
        input = last_input;
        continue;
    }
   

    //on etudie la duree de getch pour que chaque boucle ait la meme duree
    if (((stop.tv_usec - start.tv_usec) < 0 ? -1*(stop.tv_usec - start.tv_usec) : (stop.tv_usec - start.tv_usec)) <= DELAY*10000){
      usleep((DELAY*10000 - ((stop.tv_usec - start.tv_usec) < 0 ? -1*(stop.tv_usec - start.tv_usec) : (stop.tv_usec - start.tv_usec))));
    }
    gettimeofday(&start, NULL);
    input = getch();
    gettimeofday(&stop, NULL);

    //si le joueur touche un mur, on retourne a l'ecran titre (sans ca le programme segfault)
    if (player->tete_serpent.x == -1 || player->tete_serpent.y == 0 || player->tete_serpent.x == g->n || player->tete_serpent.y == g->m-1){
      desallouerListSection(player->head);
      player->head = NULL;
      free(player);
      return 1;
    }
    
    //si le joueur se touche, on retourne a l'ecran titre
    if (!strcmp(g->grid[player->tete_serpent.x][player->tete_serpent.y], "serp")){
      desallouerListSection(player->head);
      player->head = NULL;
      free(player);
      return 1;
    }

    if (!strcmp(g->grid[player->tete_serpent.x][player->tete_serpent.y], "w") && !intangible){
      desallouerListSection(player->head);
      player->head = NULL;
      free(player);
      return 1;
    }

    
    //on vide dans un premier temps la grille pour eviter les traces de serpent
    grilleVider(g);

    if (!estFruitGrille(g)){
      g->grid[g->fruit.x][g->fruit.y] = "f";
    }
    //met le nouveau serpent dans la grille et l'affiche
    grilleRemplir(g, player);
    grilleRedessiner(g);
    //si on atteint l'objectif, c'est bon
    if (score >= objective){
      desallouerListSection(player->head);
      player->head = NULL;
      free(player);
      return 0;
    }
    //fflush() s'assure de bien afficher tout ce qu'il y a dans le cache
    
    if (((stop.tv_usec - start.tv_usec) < 0 ? -1*(stop.tv_usec - start.tv_usec) : (stop.tv_usec - start.tv_usec)) <= DELAY*100000){
      usleep(DELAY*100000 - ((stop.tv_usec - start.tv_usec) < 0 ? -1*(stop.tv_usec - start.tv_usec) : (stop.tv_usec - start.tv_usec)));
    }

    fflush(stdout);

  }

  free(player);
  return 1;
}

//affichage du menu de debut de jeu
void printGameMenu(int opt){
  clear();
  int x, y;
  x = getmaxx(stdscr)/2 - 78/2;
  y = getmaxy(stdscr)/3;
  move(y, x);
  attron(COLOR_PAIR(2));
  printw(" _____  _   _  ___       ___    _   _  ___    _   _     ___    _____         ___ ");
  move(y+1, x);
  printw("(_   _)( ) ( )(  _`\\    (  _`\\ ( ) ( )(  _`\\ ( ) ( )   (  _`\\ (  _  )/'\\_/`\\(  _`\\ ");
  move(y+2, x);
  printw("  | |  | |_| || (_(_)   | (_(_)| `\\| || (_(_)| |/'/'   | ( (_)| (_) ||     || (_(_)");
  move(y+3, x);
  printw("  | |  |  _  ||  _)_    `\\__ \\ | , ` ||  _)_ | , <     | |___ |  _  || (_) ||  _)_ ");
  move(y+4, x);
  printw("  | |  | | | || (_( )   ( )_) || |`\\ || (_( )| |\\`\\    | (_, )| | | || | | || (_( ) ");
  move(y+5, x);
  printw("  (_)  (_) (_)(____/'   `\\____)(_) (_)(____/'(_) (_)   (____/'(_) (_)(_) (_)(____/'");
  
  y = y+6;
  x = getmaxx(stdscr)/2;
  move(y, x - 30/2);
  printw("Programme par : Kylian Maouchi");
  move(y+1, x - 36/2);
  printw("Appuyez sur espace pour selectionner");
  move(y+2, x - 44/2);
  printw("Utilisez 'z' et 's' pour choisir une option!");
  move(y+3, x);
  y = y+5;
  x = x - 7/2;
  switch (opt){
    case 0:
      move(y+1, x);
      attron(COLOR_PAIR(1));
      printw("Jouer!!");
      move(y+3, x);
      attron(COLOR_PAIR(2));
      printw("Tutoriel");
      move(y+5, x);
      attron(COLOR_PAIR(2));
      printw("Quitter");
      break;
    case 1:
      move(y+1, x);
      attron(COLOR_PAIR(2));
      printw("Jouer!!");
      move(y+3, x);
      attron(COLOR_PAIR(1));
      printw("Tutoriel");
      move(y+5, x);
      attron(COLOR_PAIR(2));
      printw("Quitter");
      break;
    case 2:
      move(y+1, x);
      attron(COLOR_PAIR(2));
      printw("Jouer!!");
      move(y+3, x);
      attron(COLOR_PAIR(2));
      printw("Tutoriel");
      move(y+5, x);
      attron(COLOR_PAIR(1));
      printw("Quitter");
      break;
  }
}

//affiche la cinématique de début de jeu
void printGameMenuCinematic(){
  clear();
  int x, y;
  x = getmaxx(stdscr)/2 - 78/2;
  y = getmaxy(stdscr)/3;
  move(y, x);
  attron(COLOR_PAIR(2));
  printw(" _____  _   _  ___       ___    _   _  ___    _   _     ___    _____         ___ ");
  move(y+1, x);
  printw("(_   _)( ) ( )(  _`\\    (  _`\\ ( ) ( )(  _`\\ ( ) ( )   (  _`\\ (  _  )/'\\_/`\\(  _`\\ ");
  move(y+2, x);
  printw("  | |  | |_| || (_(_)   | (_(_)| `\\| || (_(_)| |/'/'   | ( (_)| (_) ||     || (_(_)");
  move(y+3, x);
  printw("  | |  |  _  ||  _)_    `\\__ \\ | , ` ||  _)_ | , <     | |___ |  _  || (_) ||  _)_ ");
  move(y+4, x);
  printw("  | |  | | | || (_( )   ( )_) || |`\\ || (_( )| |\\`\\    | (_, )| | | || | | || (_( ) ");
  move(y+5, x);
  printw("  (_)  (_) (_)(____/'   `\\____)(_) (_)(____/'(_) (_)   (____/'(_) (_)(_) (_)(____/'");
  refresh();
  sleep(2);
  y = y+6;
  x = getmaxx(stdscr)/2;
  move(y, x - 30/2);
  printw("Programme par : Kylian Maouchi");
  move(y+1, x - 36/2);
  printw("Appuyez sur espace pour selectionner");
  move(y+2, x - 44/2);
  printw("Utilisez 'z' et 's' pour choisir une option!");
  move(y+3, x);
  refresh();
  sleep(2);
  y = y+5;
  x = x - 7/2;
  move(y+1, x);
  attron(COLOR_PAIR(1));
  printw("Jouer!!");
  refresh();
  usleep(500*1000);
  move(y+3, x);
  attron(COLOR_PAIR(2));
  printw("Tutoriel");
  refresh();
  usleep(500*1000);
  move(y+5, x);
  attron(COLOR_PAIR(2));
  printw("Quitter");
  refresh();
  return;
}

//si la tete du serpent est sur un fruit, on le fait disparaitre et on en genere un nouveau
int serpentMangeFruit(grille * g, serpent * serp){
  if (g->fruit.x == serp->tete_serpent.y && g->fruit.y == serp->tete_serpent.x){
    g->fruit.x = -1;
    g->fruit.y = -1;
    grilleTirageFruit(g);
    return 1;
  }
  return 0;
}

//fonction de gestion du corps du jeu 
//on défini plusieurs variable en fonction des objets tenu par le joueur 
//a chaque boucle, on lance la fonction gameLoopSnake et on evalue son resultat (vague reussi ou rate)
//si reussi, on lance la selection d'objet et on active les objets a une utilisation
//si perdu, on affiche l'ecran de fin de partie. Si le joueur possede plusieurs vie, on continue la vague actuelle
void gameMain(grille * g, int mode_infini){ 
  int objective = 3;
  int vie = 2;
  int less_wall = 0;
  int intangible = 0;
  int nb_max_vague = mode_infini == 0 ? MAX_WAVE : 65535;
  int result_game;
  //initialisation du repertoire de tout les objets du jeu
  listObjet * repertoire_obj = creerListObjet(serpentPeluche(initObjet()));
  ajouterObjet(repertoire_obj, pomme(initObjet()));
  ajouterObjet(repertoire_obj, helium(initObjet()));
  ajouterObjet(repertoire_obj, caillou(initObjet()));
  ajouterObjet(repertoire_obj, ticketLoterie(initObjet()));
  ajouterObjet(repertoire_obj, paquetChips(initObjet()));
  ajouterObjet(repertoire_obj, calculatrice(initObjet()));
  listObjet * itemPlayer = creerListObjet(serpentPeluche(initObjet()));

  for (int i = 1; i<=nb_max_vague; i++){
    //menu de debut de manche
    clear();
    flushinp();
    move(getmaxy(stdscr)/2, getmaxx(stdscr)/2-5);
    printw("MANCHE %d/%d", i, nb_max_vague);
    refresh();
    usleep(700*1000);
    move(getmaxy(stdscr)/3 + 3, getmaxx(stdscr)/2 - 10);
    printw("Vie restante : %5d", vie);
    refresh();
    sleep(1);
    //test de la boucle de jeu
    result_game = gameLoopSnake(g, objCount(itemPlayer, retourneObjet(repertoire_obj, POS_SERP_PEL))*2, objCount(itemPlayer, retourneObjet(repertoire_obj, POS_CHIPS))*3, objective, itemPlayer, i, less_wall, intangible);
    flushinp();
    if (result_game == 1){
      //ici, on a perdu, on diminue la vie et on recommence cette manche si il reste des vies
      clear();
      vie--;
      if (vie<=-1){
        //on termine si on a -1 vie
        sleep(1);
        clear();
        for (int n = 0; n<getmaxx(stdscr); n++){
          for (int m = 0; m<getmaxy(stdscr); m++){
            move(m, n);
            attron(COLOR_PAIR(8));
            printw(" ");
          }
        }
        refresh();
        sleep(1);
        attron(COLOR_PAIR(1));
        //detruireListObjet(itemPlayer);
        //detruireListObjet(repertoire_obj); erreur de free
        return;
      }
      move(getmaxy(stdscr)/3, getmaxx(stdscr)/2 - 12);
      printw("VOUS AVEZ PERDU BOUUUUUH");
      refresh();
      usleep(700*1000);
      move(getmaxy(stdscr)/3 + 3, getmaxx(stdscr)/2 - 10);
      printw("Vies restantes : %5d", (vie <= -1 ? 0 : vie));
      refresh();
      sleep(2);
      //on retourne en arrière d'une itération, pour continue et revenir à celle ci
      i--;
      continue;
    }
    if (result_game == 2){
      clear();
      //detruireListObjet(itemPlayer);
      //detruireListObjet(repertoire_obj); erreur de free
      return;
    }
    usleep(300*1000);
    ajouterObjet(itemPlayer, menuChoixObj(repertoire_obj));
    //actualisation des variables de jeu
    intangible = 0;
    less_wall = 0;
    objective += objective * 1.2 + 4 - (objCount(itemPlayer, retourneObjet(repertoire_obj, POS_CALC)) * 0.5 * objective);

    //fonction pour consommable
    if (posObjet(itemPlayer, retourneObjet(repertoire_obj, POS_POM)) != -1){
      vie += objCount(itemPlayer, retourneObjet(repertoire_obj, POS_POM));
      while (posObjet(itemPlayer, retourneObjet(repertoire_obj, POS_POM)) != -1){
        supprimerPosObjet(itemPlayer, posObjet(itemPlayer, retourneObjet(repertoire_obj, POS_POM)));
      }
    }

    if (posObjet(itemPlayer, retourneObjet(repertoire_obj, POS_HELIUM)) != -1){
      intangible = 1;
      while (posObjet(itemPlayer, retourneObjet(repertoire_obj, POS_HELIUM)) != -1){
        supprimerPosObjet(itemPlayer, posObjet(itemPlayer, retourneObjet(repertoire_obj, POS_HELIUM)));
      }
    }

    if (posObjet(itemPlayer, retourneObjet(repertoire_obj, POS_CAILLOU)) != -1){
      less_wall = 1;
      while (posObjet(itemPlayer, retourneObjet(repertoire_obj, POS_CAILLOU)) != -1){
        supprimerPosObjet(itemPlayer, posObjet(itemPlayer, retourneObjet(repertoire_obj, POS_CAILLOU)));
      }
    }

    if (posObjet(itemPlayer, retourneObjet(repertoire_obj, POS_TICKET)) != -1){
      if (rand()%2 == 1) i++; continue;
      while (posObjet(itemPlayer, retourneObjet(repertoire_obj, POS_TICKET)) != -1){
        supprimerPosObjet(itemPlayer, posObjet(itemPlayer, retourneObjet(repertoire_obj, POS_TICKET)));
      }
    }
  }

  if (mode_infini == 0){
    if (menuChoixModeInfini(itemPlayer)){
      gameMain(g, 1);
    }
  }

  detruireListObjet(itemPlayer);
  detruireListObjet(repertoire_obj);
  
  return;
}

//fonction d'affichage d'objet indépendant
void printObj(objet * obj, int x, int y){
  move(y, x);
  printw(obj->nom);
  move (y+2, x);
  printw(obj->descr);
  attron(COLOR_PAIR(2));
  return;
}

//3 objets sont tiré au hasard dans le repertoire d'objet, on les propose au joueur et celui ci recupere
//dans la liste l'objet voulu
objet * menuChoixObj(listObjet * repertoire){
  int x = getmaxx(stdscr)/2;
  int y = 5;
  int opt = 0;
  //variable pour l'animation d'arrive au menu
  int first_look = 1;
  objet * obj1 = retourneObjet(repertoire, rand()%listSize(repertoire));
  objet * obj2 = retourneObjet(repertoire, rand()%listSize(repertoire));
  objet * obj3 = retourneObjet(repertoire, rand()%listSize(repertoire));
  char input = 0;
  clear();
  while (input!=' '){
    move(y, x-16);
    printw("Choississez votre prochain objet!");
    input = getch();
    switch (input){
      case 'z':
        opt = opt - 1;
        if (opt < 0){
          opt = 2;
        }
        break;
      case 's':
        opt = (opt + 1)%3;
        break;
    }
    switch (opt){
      case 0:
        if (first_look){
          first_look = 0;
          attron(COLOR_PAIR(1));
          usleep(500*1000);
          printObj(obj1, getmaxx(stdscr)/3, getmaxy(stdscr)/5);
          refresh();
          usleep(500*1000);
          printObj(obj2, getmaxx(stdscr)/3, 2*getmaxy(stdscr)/5);
          refresh();
          usleep(500*1000);
          printObj(obj3, getmaxx(stdscr)/3, 3*getmaxy(stdscr)/5);
          refresh();
          break;
        }
        attron(COLOR_PAIR(1));
        printObj(obj1, getmaxx(stdscr)/3, getmaxy(stdscr)/5);
        printObj(obj2, getmaxx(stdscr)/3, 2*getmaxy(stdscr)/5);
        printObj(obj3, getmaxx(stdscr)/3, 3*getmaxy(stdscr)/5);
        break;
      case 1:
        printObj(obj1, getmaxx(stdscr)/3, getmaxy(stdscr)/5);
        attron(COLOR_PAIR(1));
        printObj(obj2, getmaxx(stdscr)/3, 2*getmaxy(stdscr)/5);
        printObj(obj3, getmaxx(stdscr)/3, 3*getmaxy(stdscr)/5);
        break;
      case 2:
        printObj(obj1, getmaxx(stdscr)/3, getmaxy(stdscr)/5);
        printObj(obj2, getmaxx(stdscr)/3, 2*getmaxy(stdscr)/5);
        attron(COLOR_PAIR(1));
        printObj(obj3, getmaxx(stdscr)/3, 3*getmaxy(stdscr)/5);
        break;
    }
    refresh();
  }
  
  switch (opt){
    case 0:
      return obj1;
      break;
    case 1:
      return obj2;
      break;
    case 2:
      return obj3;
      break;
  }
  return obj1;
}

//choix du mode infini, si oui, alors on relance gameMenu en mode infini
int menuChoixModeInfini(listObjet * itemPlayer){
  clear();
  int input = 0;
  int opt = 0;
  while (input!=' '){
    move(getmaxy(stdscr)/2, getmaxx(stdscr)/5 - 14);
    printw("Bravo vous avez fini le jeu!");
    move(getmaxy(stdscr)/2 + 2, getmaxx(stdscr)/5 - 17);
    printw("Mode infini? (objet non conservé !)");
    input = getch();
    switch (input){
      case 'q':
        opt = (opt + 1)%2;
        break;
      case 'd':
        opt = (opt + 1)%2;
        break;
    }

    switch (opt){
      case 0:
        move(getmaxy(stdscr)/2, 2*getmaxx(stdscr)/5 - 4);
        attron(COLOR_PAIR(1));
        printw("OUIII!!!!");
        attron(COLOR_PAIR(2));
        move(getmaxy(stdscr)/2, 3*getmaxx(stdscr)/5 - 10);
        printw("non... (je suis nul)");
        break;
      case 1:
        move(getmaxy(stdscr)/2, 2*getmaxx(stdscr)/5 - 4);
        printw("OUIII!!!!");
        attron(COLOR_PAIR(1));
        move(getmaxy(stdscr)/2, 3*getmaxx(stdscr)/5 - 10);
        printw("non... (je suis nul)");
        attron(COLOR_PAIR(2));
        break;
    }
    move(getmaxy(stdscr)/4, 4*getmaxx(stdscr)/5);
    printw("Vos objets :");
    printListObjet(itemPlayer, 4*getmaxx(stdscr)/5, getmaxy(stdscr)/4 + 3);
  }

  return 1 - opt;
}

//affichage de l'option tutoriel
void printTutoriel(){
  clear();
  int x = getmaxx(stdscr)/2;
  int y = getmaxy(stdscr)/5;
  move(y, x-15);
  printw("Bienvenue dans le jeu du Snek!!");
  y+=3;
  move(y, x-25);
  refresh();
  sleep(1);
  printw("Dans ce jeu, vous jouerez au jeu classique du snake");
  y++;
  move(y, x-19);
  printw("En vous déplaçant avec les touches zqsd");
  y++;
  move(y, x-24);
  printw("Appuyez sur 'p' pendant une partie pour la quitter");
  y++;
  move(y, x-24);
  printw("Mais des murs apparaissent au milieu du terrain !");
  y+=2;
  refresh();
  sleep(2);
  move(y, x-23);
  printw("Le jeu se compose de vague, battez les 5 vagues");
  y++;
  move(y, x-23);
  printw("En atteignant le score nécessaire pour gagner !");
  y+=2;
  refresh();
  sleep(2);
  move(y, x-29);
  printw("3 objets aléatoires vous seront donné à chaque fin de manche");
  y++;
  move(y, x-31);
  printw("La description de ceux-ci sont écris en dessous, bonne chance !");
  y+=7;
  move(y, x-19);
  refresh();
  sleep(3);
  attron(COLOR_PAIR(1));
  printw("Appuyez sur espace pour quitter le menu");
  attron(COLOR_PAIR(2));
  refresh();
  int input = 0;
  while (input!=' '){
    input = getch(); 
  }
  return;
}
