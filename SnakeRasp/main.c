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
  int tailleSerpent = 10;
  Coordonnees serpent[50];
  serpent[0].x = CENTRE_X_GRILLE;
  serpent[0].y = CENTRE_Y_GRILLE;
  Coordonnees queue;
  Pomme tabPomme[NB_POMME] = {};
  Obstacles tabObstacle[NB_OBSTACLE] = {};
  Coordonnees tete;
  InitialiserGraphique();
  CreerFenetre(250,100,NB_PIXEL_X_FENETRE,NB_PIXEL_Y_FENETRE);
  while(etatJeu){
    InitialiserVariable(&score,&direction,&tailleSerpent,&seconde,&minute,serpent);
    for (i = 0 ; i < NB_POMME; i++) // Initialisation du serpent
      {
	tabPomme[i].x = -1;
	tabPomme[i].y = -1;
	tabPomme[i].flagP = 0;
      }
    for (i = 1 ; i < TAILLE_MAX_SNAKE; i++) // Initialisation du serpent
      {
	serpent[i].x = -1;
	serpent[i].y = -1;
      }
    NettoyerEcran();
    RemplirRectangle(0,NB_PIXEL_Y_JEU,1080,carre*3); // Bande noir en bas
    for(i = 0; i < tailleSerpent; i++)
      {
	ChoisirCouleurDessin(CouleurParComposante(27,94,32));
	RemplirRectangle(serpent[i].x*carre,serpent[i].y*carre,carre,carre);
      }
    AfficherScore(score);
    AfficherTemps(seconde,minute,carre,&score);
    CreerObstacles(carre,tabObstacle);
    while(ToucheEnAttente() != 1)
      {
      }
    while(1)//Boucle principale
      {
	//DessinerGrille(carre);
	AfficherSerpent(serpent,tailleSerpent,carre,queue);
	direction = DirectionSerpent(direction);
	if (Microsecondes()>suivant) // Si une seconde est passé
	  {
	    suivant=Microsecondes()+delta;
	    seconde++;
	    if(seconde == 60){
	      seconde = 0;
	      minute++;
	    }
	    AfficherTemps(seconde,minute,carre,&score);
	  }
	queue = DeplacerSerpent(carre,direction,serpent,tailleSerpent);
	tete = serpent[0];
	tailleSerpent = VerifieManger(&score,tete,tabPomme,tailleSerpent,carre);
	CreerPomme(carre,tabPomme,tabObstacle,tailleSerpent,serpent);
	if(VerifieCollisionSerpent(tete,serpent,tailleSerpent,tabObstacle)){// Touche un mur => GAME OVER
	  break;
	}
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
