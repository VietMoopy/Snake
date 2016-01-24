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

Serpent* CreerSerpentVide(){
  Serpent* serpent = (Serpent*) malloc(sizeof(Serpent));
  serpent->tailleSerpent = TAILLE_INITIAL_SERPENT;
  serpent->tete = NULL;
  return serpent;
}

void AjouterElt(Serpent* serpent, Coordonnees element){
  EltSerpent* p = (EltSerpent*) malloc(sizeof(EltSerpent));
  if(serpent->tete != NULL){
    p->element = element;
    p->suivant = serpent->tete;
    p->precedent = NULL;
    serpent->tete->precedent = p;
    serpent->tete = p;
  }
  if(serpent->tete == NULL){
    p->element = element;
    p->suivant = NULL;
    p->precedent = NULL;
    serpent->tete = p;
  }
}

void Afficher(Serpent* serpent){
  EltSerpent* s;
  putchar('\n');;
  for(s = serpent->tete;s != NULL; s = s->suivant){
    printf("%d %d -> ",s->element.x,s->element.y);

    //printf("<-%p",s->precedent);
  }
  putchar('\n');
}

Coordonnees DeplacerSerpentLC(int carre,int direction, Serpent* serpent, int* compteur) // Affiche le deplacement du serpent visuellement selon la direction 
{
  Coordonnees queue = serpent->tete->element;
  EltSerpent* s;
  for(s = serpent->tete; s->suivant != NULL; s = s->suivant)
    {
      s->element = s->suivant->element;
    }
  if(direction == UP)
    {
      s->element.x =  s->element.x;
      s->element.y=  s->element.y-1;
    }
  if(direction == DOWN)
    {
      s->element.x=  s->element.x;
      s->element.y=  s->element.y+1;
    }
  if(direction == LEFT)
    {
      s->element.x=  s->element.x-1;
      s->element.y=  s->element.y;
    }
  if(direction == RIGHT)
    {
      s->element.x=  s->element.x+1;
      s->element.y= s->element.y;
    }
  return queue;
}

void AfficherSerpentLC(Serpent* serpent, int carre, Coordonnees queue){
  EltSerpent* s;
  usleep(VITESSE_SERPENT); // Vitesse du serpent
  ChoisirCouleurDessin(CouleurParNom("white"));
  RemplirRectangle(queue.x*carre,queue.y*carre,carre,carre);
  for(s = serpent->tete; s ->suivant!= NULL; s = s->suivant)
    {
      ChoisirCouleurDessin(CouleurParNom("green")); // Vert clair
      RemplirRectangle(s->element.x*carre,s->element.y*carre,carre,carre);
    }
  ChoisirCouleurDessin(CouleurParComposante(27,94,32)); // Vert fonce
  RemplirRectangle(s->element.x*carre,s->element.y*carre,carre,carre);
}

int DirectionSerpent(int direction,int* etatJeu, int* etatPartie) // Permet de determiner dans quelle direction l'utilisateur veut faire diriger le serpent
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
	  MettrePause(etatJeu,etatPartie);
	}
      if(touche == XK_Escape) // Pour quitter le jeu
	{
	  QuitterPartie(etatJeu,etatPartie);
	}
    } // Dans le cas où le joueur n'a rien pressé, on renvoit la même valeur que celle donnée en argument
  return direction;
}

int MettrePause(int* etatJeu, int* etatPartie){
  int touche = 0;
  while(ToucheEnAttente() != 1 && touche != XK_space)
    {
      touche = Touche();
      if(touche == XK_Escape) // Pour quitter le jeu
	{
	  QuitterPartie(etatJeu,etatPartie);
	  break;
	}
    }
}

void QuitterPartie(int* etatJeu, int *etatPartie){
  *etatJeu = 0;
  *etatPartie = 0;
}
  

int CreerPomme(int carre, Pomme* tabPomme, Obstacle* tabObstacle){ // Affiche une pomme au hasard sur la map
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
		}
	    }
	}
      ChoisirCouleurDessin(CouleurParNom("red"));
      RemplirRectangle(tabPomme[i].x*carre,tabPomme[i].y*carre,carre,carre);
    }
}


void CreerObstacles(int carre, Obstacle* tabObstacle){ // Affiche une pomme au hasard sur la map
  int i;
  for(i = 0; i < NB_OBSTACLE; i++)
    {
      tabObstacle[i].x = (rand() % (MAXGRILLEX - MINGRILLE + 1)) + MINGRILLE; // Permet d'obtenir une valeur aléatoire entre 0 et 60 sachant que la grille est de 60 par 40
      tabObstacle[i].y = (rand() % (MAXGRILLEY - MINGRILLE + 1)) + MINGRILLE; // Permet d'obtenir une valeur aléatoire entre 0 et 40
      ChoisirCouleurDessin(CouleurParNom("black"));
      RemplirRectangle(tabObstacle[i].x*carre,tabObstacle[i].y*carre,carre,carre); // On multiplie les valeurs aléatoires obtenues à la taille d'un carré afin d'obtenir une position aléatoire d'un carré
    }
}

void VerifieManger(Serpent* serpent,int* score,Pomme* tabPomme,int carre)
{
  int i;
  EltSerpent* s;
  for(s = serpent->tete; s ->suivant!= NULL; s = s->suivant);
  Coordonnees tete = s->element;
  Coordonnees elt = {serpent->tete->element.x,serpent->tete->element.y};
  for(i = 0; i < NB_POMME; i++)
    {
      if (tete.x == tabPomme[i].x && tete.y == tabPomme[i].y)
	{
	  tabPomme[i].flagP = 0;
	  serpent->tailleSerpent++;
	  *score = *score+5;
	  AfficherScore(*score);
	  AjouterElt(serpent,elt);
	}
    }
}

int VerifieCollisionSerpent(Serpent* serpent, Obstacle* tabObstacle)
{
  EltSerpent* s;
  Coordonnees teteS;
  int i;
  for(s = serpent->tete; s->suivant != NULL; s = s->suivant);
  teteS = s->element;
  for(s = serpent->tete; s ->suivant!= NULL; s = s->suivant){
    if (s->element.x == teteS.x && s->element.y == teteS.y)
      {
	return 1;
      }
  }
  if(teteS.x < 0 || teteS.x >= 60 || teteS.y < 0 || teteS.y >= 40 )
    {
      return 1;
    }
  for(i = 0; i < NB_OBSTACLE; i++)
    {
      if (teteS.x == tabObstacle[i].x && teteS.y == tabObstacle[i].y)
	{
	  return 1;
	}
    }
  return 0;
}

void DetruireSerpent(Serpent* serpent){
  EltSerpent* s;
  for(s = serpent->tete;s != NULL; s = s->suivant){
    s = serpent->tete;
    serpent->tete = serpent->tete->suivant;
    free(s);
  }
  free(serpent->tete);
}

void InitialiserVariable(int* score, int* direction,int* seconde, int* minute,Serpent* serpent, int* compteur, Pomme* tabPomme){
  int i;
  serpent->tailleSerpent = TAILLE_INITIAL_SERPENT;
  Coordonnees centre = {CENTRE_X_GRILLE,CENTRE_Y_GRILLE};
  Coordonnees initElt = {-1,-1}; //Corps
  AjouterElt(serpent,centre);
  for(i = 1; i < serpent->tailleSerpent; i++){
    AjouterElt(serpent,initElt);
  }
  *score = 0;
  *direction = 0;
  *seconde = 0;
  *minute = 0;
  *compteur = 0;
  for (i = 0 ; i < NB_POMME; i++) // Initialisation du serpent
    {
      tabPomme[i].x = -1;
      tabPomme[i].y = -1;
      tabPomme[i].flagP = 0;
    }
}

void CreerNouvellePartie(int* carre,int* score,int* seconde,int* minute,Obstacle* tabObstacle){
  NettoyerEcran();
  RemplirRectangle(0,NB_PIXEL_Y_JEU,1080,(*carre)*3); // Bande noir en bas
  ChoisirCouleurDessin(CouleurParComposante(27,94,32));
  RemplirRectangle(CENTRE_X_GRILLE*(*carre),CENTRE_Y_GRILLE*(*carre),*carre,*carre); // Affiche un carre vert au centre de la map
  AfficherScore(*score);
  AfficherTemps(*seconde,*minute,*carre);
  CreerObstacles(*carre,tabObstacle);
}

void AfficherGameOver(){
  ChoisirCouleurDessin(CouleurParNom("red"));
  EcrireTexte(340,260,"Vous avez perdu !",2);	
  EcrireTexte(120,290,"Appuyez sur n'importe quelle touche pour recommencer",2);
  EcrireTexte(260,320,"Appuyez sur Echap pour quitter",2);
}

#endif /* CONSTANTES.H*/
#endif /* STRUCTURES.H*/
#endif /* JEU.H*/
#endif /* AFFICHAGE.H*/
