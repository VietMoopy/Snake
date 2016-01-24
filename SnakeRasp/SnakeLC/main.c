#ifndef CONSTANTES_H
#define CONSTANTES_H
#ifndef STRUCTURES_H
#define STRUCTURES_H
#ifndef JEU_H
#define JEU_H
#ifndef AFFICHAGE_H
#define AFFICHAGE_H
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <graph.h>
#include <time.h>
#include "constantes.h"
#include "structures.h" // Definition des structures de variable
#include "jeu.h"
#include "affichage.h"

int main() // Fonction principale
{
  srand(time(NULL));
  int carre = NB_PIXEL_X_JEU/60;
  unsigned long suivant;
  suivant= Microsecondes()+delta;
  int etatJeu = 1;
  int etatPartie = 1;
  int score,direction,seconde,minute,compteur,i;
  Coordonnees queue;
  Serpent* serpent = CreerSerpentVide();
  Pomme tabPomme[NB_POMME] = {};
  Obstacle tabObstacle[NB_OBSTACLE] = {};
  FILE* fichier = NULL;
  fichier = fopen("scoreboard.txt", "w");
  char nom[50];
  printf("Entrez votre pseudo : ");
  fgets(nom, 50, stdin);
  InitialiserGraphique();
  CreerFenetre(250,100,NB_PIXEL_X_FENETRE,NB_PIXEL_Y_FENETRE);

  while(etatJeu){
    InitialiserVariable(&score,&direction,&seconde,&minute,serpent,&compteur,tabPomme);
    CreerNouvellePartie(&carre,&score,&seconde,&minute,tabObstacle);
    while(direction == 0){
      direction = DirectionSerpent(direction,&etatJeu,&etatPartie);
	}
    while(etatPartie)//Boucle principale
      {
	direction = DirectionSerpent(direction,&etatJeu,&etatPartie);
	queue = DeplacerSerpentLC(carre,direction,serpent,&compteur);
	if(compteur < 2 && direction != 0){
	compteur++;
	}
	if (Microsecondes()>suivant) // Si une seconde est passé
	  {
	    suivant=Microsecondes()+delta;
	    seconde++;
	    if(seconde == 60){
	      seconde = 0;
	      minute++;
	    }
	    AfficherTemps(seconde,minute,carre);
	  }
	VerifieManger(serpent,&score,tabPomme,carre);
	CreerPomme(carre,tabPomme,tabObstacle);
      	if(VerifieCollisionSerpent(serpent,tabObstacle) && compteur > 1){// Touche un mur => GAME OVER
	  DetruireSerpent(serpent);
	  break;
	  }
	AfficherSerpentLC(serpent,carre,queue);
      }
    while(ToucheEnAttente() != 1 && etatJeu == 1)
      { 
	fprintf(fichier,"%s Temps %02d:%02d   Score : %07d\n\n",nom,minute,seconde,score);
	AfficherGameOver();
	if(Touche() == XK_Escape){
	  QuitterPartie(&etatJeu,&etatPartie);
	}
	else{
	  break;
	}
      }
  }
  fclose(fichier);
  FermerGraphique();
  return EXIT_SUCCESS;
}
#endif /* CONSTANTES.H*/
#endif /* STRUCTURES.H*/
#endif /* JEU.H*/
#endif /* AFFICHAGE.H*/
