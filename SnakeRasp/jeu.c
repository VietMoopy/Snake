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

int DirectionSerpent(int direction) // Permet de determiner dans quelle direction l'utilisateur veut faire diriger le serpent
{
  int touche = 0;
  if(ToucheEnAttente()) // Si le joueur a presser une touche 
    {
      touche = Touche();
      if(touche== XK_Up && direction != DOWN)
	{
	  direction = UP;
	}
      if(touche == XK_Down && direction != UP)
	{
	  direction = DOWN;
	}
      if(touche == XK_Left && direction != RIGHT)
	{
	  direction = LEFT;
	}
      if(touche == XK_Right && direction != LEFT)
	{
	  direction = RIGHT;
	}
      if(touche == XK_space)
	{
	  MettrePause();
	}
      if(touche == XK_Escape) // Pour quitter le jeu
	{
	  FermerGraphique();
	}
    } // Dans le cas où le joueur n'a rien pressé, on renvoit la même valeur que celle donnée en argument
  return direction;
}

int MettrePause(){
  int touche = 0;
  while(ToucheEnAttente() != 1 && touche != XK_space)
    {
      touche = Touche();
      if(touche == XK_Escape) // Pour quitter le jeu
	{
	  FermerGraphique();
	}
    }
}

  
Coordonnees DeplacerSerpent(int carre,int direction, Coordonnees* serpent, int tailleSerpent) // Affiche le deplacement du serpent visuellement selon la direction 
{
  int i = 0;
  Coordonnees queue = {serpent[tailleSerpent-1].x,serpent[tailleSerpent-1].y};
  for(i = tailleSerpent-1; i > 0; i--)
    {
      serpent[i].x = serpent[i-1].x;
    }
  for(i = tailleSerpent-1; i > 0; i--)
    {
      serpent[i].y = serpent[i-1].y;
    }
  if(direction == UP)
    {
      serpent[0].x= serpent[0].x;
      serpent[0].y= serpent[0].y-1;
    }
  if(direction == DOWN)
    {
      serpent[0].x= serpent[0].x;
      serpent[0].y= serpent[0].y+1;
    }
  if(direction == LEFT)
    {
      serpent[0].x= serpent[0].x-1;
      serpent[0].y= serpent[0].y;
    }
  if(direction == RIGHT)
    {
      serpent[0].x= serpent[0].x+1;
      serpent[0].y= serpent[0].y;
    }
  return queue;
}

void AfficherSerpent(Coordonnees* serpent, int tailleSerpent, int carre, Coordonnees queue){
  int i = 0;
  usleep(60000); // Vitesse du serpent
  ChoisirCouleurDessin(CouleurParNom("white"));
  RemplirRectangle(queue.x*carre,queue.y*carre,carre,carre);
  ChoisirCouleurDessin(CouleurParComposante(27,94,32)); // Vert fonce
  RemplirRectangle(serpent[0].x*carre,serpent[0].y*carre,carre,carre);
  for(i = 1; i < tailleSerpent; i++)
    {
      ChoisirCouleurDessin(CouleurParNom("green")); // Vert clair
      RemplirRectangle(serpent[i].x*carre,serpent[i].y*carre,carre,carre);
    }
}


int CreerPomme(int carre, Pomme* tabPomme, Obstacles* tabObstacle, int tailleSerpent, Coordonnees* serpent){ // Affiche une pomme au hasard sur la map
  int i,j,k;
  for(i = 0; i < NB_POMME; i++)
    {
      if(tabPomme[i].flagP == 0) // Si il n'y a pas de pomme sur la map
	{
	  tabPomme[i].flagP = 1;
	  tabPomme[i].x = (rand() % (MAXGRILLEX - MINGRILLE + 1)) + MINGRILLE;
	  tabPomme[i].y = (rand() % (MAXGRILLEY - MINGRILLE + 1)) + MINGRILLE;
	  for(k = 0;  k < NB_OBSTACLE; k++)
	    {		
	      while(tabPomme[i].x == tabObstacle[k].x && tabPomme[i].y == tabObstacle[k].y)
		{
		  tabPomme[i].x = (rand() % (MAXGRILLEX - MINGRILLE + 1)) + MINGRILLE; // Permet d'obtenir une valeur aléatoire entre 0 et 60 sachant que la grille est de 60 par 40
		  tabPomme[i].y = (rand() % (MAXGRILLEY - MINGRILLE + 1)) + MINGRILLE; // Permet d'obtenir une valeur aléatoire entre 0 et 40
		  for(j = 1; j < tailleSerpent; j++)
		    {
		      if(tabPomme[i].x == serpent[j].x && tabPomme[i].x == serpent[j].y)
			{
			  tabPomme[i].x = (rand() % (MAXGRILLEX - MINGRILLE + 1)) + MINGRILLE; // Permet d'obtenir une valeur aléatoire entre 0 et 60 sachant que la grille est de 60 par 40
			  tabPomme[i].y = (rand() % (MAXGRILLEY - MINGRILLE + 1)) + MINGRILLE; // Permet d'obtenir une valeur aléatoire entre 0 et 40
			}
		    }
		}
	    }
	}
      ChoisirCouleurDessin(CouleurParNom("red"));
      RemplirRectangle(tabPomme[i].x*carre,tabPomme[i].y*carre,carre,carre);
    }  
}

  


void CreerObstacles(int carre, Obstacles* tabObstacle){ // Affiche une pomme au hasard sur la map
  int i;
  for(i = 0; i < NB_OBSTACLE; i++)
    {
      tabObstacle[i].x = (rand() % (MAXGRILLEX - MINGRILLE + 1)) + MINGRILLE; // Permet d'obtenir une valeur aléatoire entre 0 et 60 sachant que la grille est de 60 par 40
      tabObstacle[i].y = (rand() % (MAXGRILLEY - MINGRILLE + 1)) + MINGRILLE; // Permet d'obtenir une valeur aléatoire entre 0 et 40
      ChoisirCouleurDessin(CouleurParNom("black"));
      RemplirRectangle(tabObstacle[i].x*carre,tabObstacle[i].y*carre,carre,carre); // On multiplie les valeurs aléatoires obtenues à la taille d'un carré afin d'obtenir une position aléatoire d'un carré
    }
}

int VerifieManger(int* score,Coordonnees tete,Pomme* tabPomme, int tailleSerpent,int carre)
{
  int i;
  for(i = 0; i < NB_POMME; i++)
    {
      if (tete.x == tabPomme[i].x && tete.y == tabPomme[i].y)
	{
	  tabPomme[i].flagP = 0;
	  tailleSerpent++;
	  *score = *score+5;
	  AfficherScore(*score);
	}
    }
  return tailleSerpent;
}



int VerifieCollisionSerpent(Coordonnees tete, Coordonnees serpent[], int tailleSerpent, Obstacles* tabObstacle)
{
  int i;
  int k;
  for(i = 1; i < tailleSerpent; i++)
    {
      if (tete.x == serpent[i].x && tete.y == serpent[i].y)
	{
	  return 1;
	}
    }
  if(tete.x < 0 || tete.x >= 60 || tete.y < 0 || tete.y >= 40 )
    {
      return 1;
    }
  for(k = 0; k < NB_OBSTACLE; k++)
    {
      if (tete.x == tabObstacle[k].x && tete.y == tabObstacle[k].y)
	{
	  return 1;
	}
    }
  return 0;
}


void InitialiserVariable(int* score, int* direction,int* tailleSerpent,int* seconde, int* minute, Coordonnees* serpent){
  *score = 0;
  *direction = 0;
  *tailleSerpent = 10;
  *seconde = 0;
  *minute = 0;
  serpent[0].x = CENTRE_X_GRILLE;
  serpent[0].y = CENTRE_Y_GRILLE;
}

#endif /* CONSTANTES.H*/
#endif /* STRUCTURES.H*/
#endif /* JEU.H*/
#endif /* AFFICHAGE.H*/
