#ifndef CONSTANTES_H
#define CONSTANTES_H
#ifndef STRUCTURES_H
#define STRUCTURES_H
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <graph.h>
#include <time.h>
#include "constantes.h"
#include "structures.h" // Definition des structures de variable

void DessinerGrille(int carre) // Fonction qui dessine la grille du jeu (60x40)
{
  ChoisirCouleurDessin(CouleurParNom("black"));
  int i;
  for(i = 0; i <= NB_PIXEL_X_JEU; i = i+carre)
    {
      DessinerSegment(i,0,i,NB_PIXEL_Y_JEU);
    }
  for(i = 0; i <= NB_PIXEL_Y_JEU; i = i+carre)
    {
      DessinerSegment(0,i,NB_PIXEL_X_JEU,i);
    }
}

void CalculerTemps(char* seconde, char* seconde2, char* minute, char* minute2) // Calcule le temps, ajoute 1 à seconde toutes les secondes
{
  *seconde = *seconde + 1;
  if(*seconde == 58) // Si on a 10 secondes, on rajoute 1 au dizaine de seconde
    {
      *seconde = '0';
      *seconde2 = *seconde2 + 1;
    }
  if(*seconde2 == 54) // Si on a 60 secondes, on rajoute 1 min
    {
      *seconde2 = '0';
      *minute = *minute + 1;
    }
  if(*minute == 58) // Si on a 10 min, on rajoute 1 au dizaine de min
    {
      *minute = '0';
      *minute2 = *minute2 + 1;
    }

}

int DirectionSerpent(direction) // Permet de determiner dans quelle direction l'utilisateur veut faire diriger le serpent
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
    } // Dans le cas où le joueur n'a rien pressé, on renvoit la même valeur que celle donnée en argument
  return direction;
}

int MettrePause(){
  int touche = 0;
  while(ToucheEnAttente() != 1 && touche != XK_space)
    {
      touche = Touche();
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
  usleep(80000); // Vitesse du serpent
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


int CreerPomme(int carre, Pomme* tabPomme, Obstacles* tabObstacle){ // Affiche une pomme au hasard sur la map
  int i,k;
  srand(time(NULL));
  for(i = 0; i < NB_POMME; i++)
    {
      if(tabPomme[i].flagP == 0) // Si il n'y a pas de pomme sur la map
	{
	  tabPomme[i].flagP = 1;
	  for(k = 0; k < NB_OBSTACLE; k++)
	    {
	      tabPomme[i].x = (rand() % (MAXGRILLEX - MINGRILLE + 1)) + MINGRILLE;
	      tabPomme[i].y = (rand() % (MAXGRILLEY - MINGRILLE + 1)) + MINGRILLE;
	      if((tabPomme[i].x == tabObstacle[k].x && tabPomme[i].y == tabObstacle[k].y) || (tabPomme[i].x == -1 && tabPomme[i].y == -1))
		{
		  tabPomme[i].x = (rand() % (MAXGRILLEX - MINGRILLE + 1)) + MINGRILLE; // Permet d'obtenir une valeur aléatoire entre 0 et 60 sachant que la grille est de 60 par 40
		  tabPomme[i].y = (rand() % (MAXGRILLEY - MINGRILLE + 1)) + MINGRILLE; // Permet d'obtenir une valeur aléatoire entre 0 et 40
		}
	    }
	  ChoisirCouleurDessin(CouleurParNom("red"));
	  RemplirRectangle(tabPomme[i].x*carre,tabPomme[i].y*carre,carre,carre); // On multiplie les valeurs aléatoires obtenues à la taille d'un carré afin d'obtenir une position aléatoire d'un carré
	}
    }
}
  
void AfficherScore(int score)
{ 
  char scoreTab[8] = {'0','0','0','0','0','0','0','\0'};
  sprintf(scoreTab,"%07d",score);
  ChoisirCouleurDessin(CouleurParNom("black"));
  RemplirRectangle(500,NB_PIXEL_Y_JEU,340,54);
  ChoisirCouleurDessin(CouleurParNom("white"));
  EcrireTexte(740,590,scoreTab,2);
}

void CreerObstacles(int carre, Obstacles* tabObstacle){ // Affiche une pomme au hasard sur la map
  int i;
  srand(time(NULL));
  for(i = 0; i < NB_OBSTACLE; i++)
    {
      tabObstacle[i].x = (rand() % (MAXGRILLEX - MINGRILLE + 1)) + MINGRILLE; // Permet d'obtenir une valeur aléatoire entre 0 et 60 sachant que la grille est de 60 par 40
      tabObstacle[i].y = (rand() % (MAXGRILLEY - MINGRILLE + 1)) + MINGRILLE; // Permet d'obtenir une valeur aléatoire entre 0 et 40
      ChoisirCouleurDessin(CouleurParNom("black"));
      RemplirRectangle(tabObstacle[i].x*carre,tabObstacle[i].y*carre,carre,carre); // On multiplie les valeurs aléatoires obtenues à la taille d'un carré afin d'obtenir une position aléatoire d'un carré
    }
}

int VerifieManger(int* score,Coordonnees tete,Pomme* tabPomme, int tailleSerpent)
{
  int i;
  for(i = 0; i < NB_OBSTACLE; i++)
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

void AfficherTemps(char seconde, char seconde2, char minute, char minute2, int carre, int* score) // Fonction qui affiche le temps
{
  char tempsTab[6] = {'0','0',':','0','0','\0'}; // On remplace chaque membre par la valeur du temps qu'on a calculé grace à la fonction précédente
  int temps = 0;;
  char min = 0;
  ChoisirCouleurDessin(CouleurParNom("black"));
  tempsTab[0] = minute2;
  tempsTab[1] = minute;
  tempsTab[3] = seconde2;	
  tempsTab[4] = seconde; 
  RemplirRectangle(0,NB_PIXEL_Y_JEU,500,54);
  ChoisirCouleurDessin(CouleurParNom("white"));
  EcrireTexte(30,590,tempsTab,2);
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

void NettoyerEcran(){
  ChoisirCouleurDessin(CouleurParNom("white"));
  RemplirRectangle(0,0,NB_PIXEL_X_JEU,NB_PIXEL_Y_JEU);
}
  
void InitialiserVariable(int* score, int* direction, char* seconde, char* seconde2, char* minute,char* minute2,int* tailleSerpent){
  *score = 0;
  *direction = 0;
  *seconde = '0';
  *seconde2 = '0';
  *minute = '0';
  *minute2 = '0';
  *tailleSerpent = 10;
}
  

int main() // Fonction principale
{
  int carre = NB_PIXEL_X_JEU/60;
  unsigned long suivant;
  suivant= Microsecondes()+delta;
  int i = 0;
  int etatJeu = 1;
  int score = 0;
  int direction = 0;
  char seconde = '0';
  char seconde2 = '0';
  char minute = '0';
  char minute2 = '0';
  int tailleSerpent = 10;
  Coordonnees serpent[20];

  serpent[tailleSerpent].x = -1; // Pour ne pas voir un carre noir qui apparait en haut a droite de la fenetre
  serpent[tailleSerpent].y = -1;
  Coordonnees queue;
  Pomme tabPomme[NB_POMME] = {};

  Obstacles tabObstacle[NB_OBSTACLE] = {};
  Coordonnees tete;
  InitialiserGraphique();
  CreerFenetre(10,10,NB_PIXEL_X_FENETRE,NB_PIXEL_Y_FENETRE);
  while(etatJeu){
    InitialiserVariable(&score,&direction,&seconde,&seconde2,&minute,&minute2,&tailleSerpent);
    for (i = 0 ; i < NB_POMME; i++) // Initialisation du serpent
      {
	tabPomme[i].x = -1;
	tabPomme[i].y = -1;
	tabPomme[i].flagP = 0;
      }
    for (i = 0 ; i < tailleSerpent; i++) // Initialisation du serpent
      {
	serpent[i].x = 30;
	serpent[i].y = 20;
      }
    NettoyerEcran();
    // DessinerGrille(carre);
    RemplirRectangle(0,NB_PIXEL_Y_JEU,1080,carre*3); // Bande noir en bas
    for(i = 0; i < tailleSerpent; i++)
      {
	ChoisirCouleurDessin(CouleurParComposante(27,94,32));
	RemplirRectangle(serpent[i].x*carre,serpent[i].y*carre,carre,carre);
      }
    AfficherScore(score);
    AfficherTemps(seconde,seconde2,minute,minute2,carre, &score);
    CreerObstacles(carre,tabObstacle);
    while(ToucheEnAttente() != 1)
      {
      }
    while(1)//Boucle principale
      {
	CreerPomme(carre,tabPomme,tabObstacle);
	// DessinerGrille(carre);
	direction = DirectionSerpent(direction);
	if (Microsecondes()>suivant) // Si une seconde est passé
	  {
	    suivant=Microsecondes()+delta;
	    AfficherTemps(seconde,seconde2,minute,minute2,carre, &score);
	    CalculerTemps(&seconde, &seconde2, &minute, &minute2);
	  }
	queue = DeplacerSerpent(carre,direction,serpent,tailleSerpent);
	tete = serpent[0];
	tailleSerpent = VerifieManger(&score,tete,tabPomme,tailleSerpent);
	if(VerifieCollisionSerpent(tete,serpent,tailleSerpent,tabObstacle)){// Touche un mur => GAME OVER
	  break;
	}
	AfficherSerpent(serpent,tailleSerpent,carre,queue);
      }
    while(ToucheEnAttente() != 1)
      { 
	ChoisirCouleurDessin(CouleurParNom("red"));
	EcrireTexte(340,260,"Vous avez perdu !",2);	
	EcrireTexte(120,290,"Appuyez sur n'importe quelle touche pour recommencer",2);
	EcrireTexte(260,320,"Appuyez sur Echap pour quitter",2);	
      }
    if(Touche() == XK_Escape)
      {
	break;
      }
  }
  FermerGraphique();
  return EXIT_SUCCESS;
}
#endif /* CONSTANTES.H*/
#endif /* STRUCTURES.H*/
