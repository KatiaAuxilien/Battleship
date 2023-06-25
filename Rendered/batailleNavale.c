#include "biblioNavale.h"
#include <stdio.h>
#include <stdlib.h>

/*Repartition charge de travail PEREIRA=50% AUXILIEN=50%*/
/*compterPts_finirTour -> FONCTION QUI DETERMINE LE COMPORTEMENT À LA FIN D'UN
 * TOUR*/
/* On utilise la fonction compterPts_finirTour qui prend en arguement l'état de
  la partie après qu'un joueur ai joué, par le biai de la fonction jouerJoueur.

  Elle renvoie au joueur l'état de la grille du joueur adverse après sont tour.
  Elle ajoute aux compteur +1 à cptrJn[5] et cptrJn[etat] si un bateau est
  touché. Ensuite, elle retournera 1 si tout va bien on passe au tour suivant, 0
  si le Jn doit rejouer. */

int compterPts_finirTour(int etat, int cptrJn[6]) {
  int passage = 0;

  if (etat == -1) {
    printf("A l'eau !\n");
    passage = 1;
  }
  
  /* On gère les cas où le joueur rejoue, et où on renvoie un tour. */

  /*Les erreurs : */
  if (etat == -2) {
    printf("Mauvais coup, vous avez déjà joué sur cette case. Rejouez.\n");
  }
  if (etat == -3) {
    printf("Hors du plateau ou entrée incorrecte. Rejouez.\n");
  }

  /*Les touches et les bateaux coulés.*/
  if (etat >= 0) {
    printf("Touché !\n");
    cptrJn[5]++;
    cptrJn[etat]++;

    if ((cptrJn[0] == 5) || (cptrJn[1] == 4) || (cptrJn[2] == 3) ||
        (cptrJn[3] == 3) || cptrJn[4] == 2) {
      /* Si un bateau a été coulé, on l'annonce et on rajoute 1 au compteur de
    coups sur ce bateau */
      printf("Tu as coulé le %s.\n", navire(etat));
      cptrJn[etat]++;
    }
  }
  return passage;
}

/*
Tableau compteur :
        cptJn[0] = compteur Porte avion, longueur = 5
        cptJn[1] = compteur Croiseur, longueur = 4
        cptrJn[2] = compteur Sous-Marin longueur = 3
        cptrJn[3] = compteur Mous-Sarin longueur = 3
        cptrJn[4] = compteur Torpilleur longueur = 2

        cptrJn[5] = Compteut total de 'touché'. max = 17

Fonction navire :
        0 Porte-Avion
        1 Croiseur
        2 Sous-Marin
        3 Mous-Sarin
        4 Torpilleur

Fonction jouerJoueur :
          -1 si le coup est à l'eau
           0 si le coup touche le Porte-Avion
           1 si le coup touche le Croiseur
           2 si le coup touche le Sous-Marin
           3 si le coup touche le Mous-Sarin
           4 si le coup touche le Torpilleur
          -2 si la case contient un caractère non reconnu (ne devrait pas
arriver) -3 si le coup est hors plateau
*/

int main(void) {

  /* INITIALISATION DES VARIABLES */

  /* On prépare les grilles vides des deux joueurs */
  char grilleJ1[10][10], grilleJ2[10][10];

  /* On prépare un compteur pour chaque joueur :
  • la case [5] correspond au nombre total de cases touchées
    contenant un bateau
  • les cases de [0] à [4] correspondent au
    nombre de cases touchées contenant un certain bateau :
      cptJn[0] = compteur Porte avion,
      cptJn[1] = compteur Croiseur,
      cptrJn[2] = compteur Sous-Marin
      cptrJn[3] = compteur Mous-Sarin
      cptrJn[4] = compteur Torpilleur

  On prépare une variable etat pour l'état de la case touchée par
  un joueur (conforme aux valeurs renvoyées par la fonction
  jouerJoueur) et une variable tour pour savoir quel joueur doit jouer
  */

  int cptJ1[6] = {}, cptJ2[6] = {}, etat, tour = 1;

  /* On initialise les grilles */
  /*J1*/
  printf("Joueur 1 : \n");
  initPlateau(grilleJ1);
  affiche(grilleJ1);
  /*J2*/
  printf("Joueur 2 : \n");
  initPlateau(grilleJ2);
  affiche(grilleJ2);

  /*  BOUCLE DE LA PARTIE  */

  while (cptJ1[5] < 17 && cptJ2[5] < 17) {
    /* On affiche la grille et le nom du joueur qui joue au début de chaque tour
     */
    printf("Le joueur %d joue.\n", tour);
    afficheduo(grilleJ1, grilleJ2);

    /* Si tour vaut 1, J1 joue
      Si compterPts_finirTour renvoie 1 on passe au Joueur 2 via
      l'addition
      Si compterPts_finirTour renvoie 0 le joueur 1 rejoue.
    */

    if (tour == 1) {

      etat = jouerJoueur(grilleJ2);
      tour += compterPts_finirTour(etat, cptJ1);
    }

    /* Le J2 joue, tour vaut 2, si etat renvoie 1 on passe au Joueur 1, via la
      soustraction, si renvoie 0 le joueur 2 rejouera. */
    else {
      etat = jouerJoueur(grilleJ1);
      tour -= compterPts_finirTour(etat, cptJ2);
    }
  }

  /* On affiche un message pour annoncer la victoire d'un joueur */
  int gagnant = (cptJ1[5] == 17) ? 1 : 2;
  printf("Bravo joueur %d ! Vous avez gagné !\n", gagnant);

  return 0;
}