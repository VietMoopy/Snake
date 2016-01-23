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
  int i = 0;
  int etatJeu = 1;
  int score = 0;
  int direction = 0;
  int seconde = 0;
  int minute = 0;
  int compteur = 0;
  Coordonnees queue;
  
  Serpent* serpent = CreerSerpentVide();
  Pomme tabPomme[NB_POMME] = {};
  Obstacles tabObstacle[NB_OBSTACLE] = {};
  InitialiserGraphique();
  CreerFenetre(250,100,NB_PIXEL_X_FENETRE,NB_PIXEL_Y_FENETRE);
  while(etatJeu){
    InitialiserVariable(&score,&direction,&seconde,&minute,serpent,&compteur);
    Afficher(serpent);
    for (i = 0 ; i < NB_POMME; i++) // Initialisation du serpent
      {
	tabPomme[i].x = -1;
	tabPomme[i].y = -1;
	tabPomme[i].flagP = 0;
      }
    NettoyerEcran();
    RemplirRectangle(0,NB_PIXEL_Y_JEU,1080,carre*3); // Bande noir en bas
    ChoisirCouleurDessin(CouleurParComposante(27,94,32));
    RemplirRectangle(CENTRE_X_GRILLE*carre,CENTRE_Y_GRILLE*carre,carre,carre); // Affiche un carre vert
    AfficherScore(score);
    AfficherTemps(seconde,minute,carre);
    CreerObstacles(carre,tabObstacle);
    while(ToucheEnAttente() != 1)
      {
      }
    while(1)//Boucle principale
      {
	//DessinerGrille(carre);
	//AfficherScore(score);
	queue = DeplacerSerpentLC(carre,direction,serpent,&compteur);
	if(compteur < 2 && direction != 0){
	compteur++;
	}
	direction = DirectionSerpent(direction);
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
    while(ToucheEnAttente() != 1)
      { 
	ChoisirCouleurDessin(CouleurParNom("red"));
	EcrireTexte(340,260,"Vous avez perdu !",2);	
	EcrireTexte(120,290,"Appuyez sur n'importe quelle touche pour recommencer",2);
	EcrireTexte(260,320,"Appuyez sur Echap pour quitter",2);	
      }
  }
  FermerGraphique();
  return EXIT_SUCCESS;
}
#endif /* CONSTANTES.H*/
#endif /* STRUCTURES.H*/
#endif /* JEU.H*/
#endif /* AFFICHAGE.H*/
