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
#include "structures.h"
#include "jeu.h"
#include "affichage.h"

int main() // Fonction principale
{
  srand(time(NULL));
  int carre = NB_PIXEL_X_JEU/60;
  unsigned long suivant;
  suivant= Microsecondes()+delta;
  int etatJeu = 1;
  int score,direction,seconde,minute,compteur,i,etatPartie;
  Coordonnees queue;
  Serpent* serpent = CreerSerpentVide();
  Pomme tabPomme[NB_POMME] = {};
  Obstacle tabObstacle[NB_OBSTACLE] = {};
  FILE* fichier = NULL;
  fichier = fopen("scoreboard.txt", "a"); // Ouvre le fichier qui va contenir les scores du jouer, on ajoute les scores à la suite avec la permission "a"
  char nom[50];

  printf("Entrez votre pseudo : ");
  fgets(nom, 50, stdin); // Demande au joueur sous quel nom il veut attribuer ses scores
  InitialiserGraphique();
  CreerFenetre(250,100,NB_PIXEL_X_FENETRE,NB_PIXEL_Y_FENETRE);
  while(etatJeu){ // Boucle principale du jeu, tant que le joueur n'a pas appuyé sur Echap, alors l'etat du jeu est 1
    InitialiserVariable(&score,&direction,&seconde,&minute,serpent,&compteur,tabPomme,&etatPartie);
    CreerNouvellePartie(&carre,&score,&seconde,&minute,tabObstacle);
    while(direction == 0){ // Tant que le joueur n'a pas pressé une touche directionnelle 
      direction = DirectionSerpent(direction,&etatJeu,&etatPartie);
    }
    while(etatPartie)//Boucle principale de la partie
      {
	direction = DirectionSerpent(direction,&etatJeu,&etatPartie);
	queue = DeplacerSerpentLC(carre,direction,serpent,&compteur);
	if(compteur < 2 && direction != 0){ /* Cette condition est présente afin d'empêcher qu'en début de partie avant même que le serpent se déploie, c'est à dire qu'on ne voit que la tête, que le joueur perde. En effet, les coordonnees de la tête vont se propager une fois sur l'element qui va le preceder donc leurs coordonnees seront égales (ce qui provoque la défaite alors que le serpent ne s'est pas encore deployé visuellement) avant ensuite d'etre definitivement différent tout le long de la partie à moins que le serpent collisionne bel et bien une partie de son corps.*/
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
	if(VerifieCollisionSerpent(serpent,tabObstacle) && compteur > 1){ // Si cette fonction renvoie 1 et que le compteur(vu précedemment) est supérieur à 1, alors le joueur a perdu
	  DetruireSerpent(serpent); // Dans ce cas, on détruit le serpent
	  etatPartie = 0; 
	  break; // On sort de la boucle de la partie
	}
	VerifieManger(serpent,&score,tabPomme,carre);
	CreerPomme(carre,tabPomme,tabObstacle);
	AfficherSerpentLC(serpent,carre,queue);
      }
    fprintf(fichier,"%s Temps %02d:%02d   Score : %07d\n\n",nom,minute,seconde,score); // On ecrit son score,temps et nom dans le fichier
    while(ToucheEnAttente() != 1 && etatJeu == 1) // Tant que le joueur n'a rien appuyé que l'etatJeu est égale 1 (c-a-d que le joueur n'a pas appuyé Echap)
      { 
	AfficherGameOver(); // On affiche le GameOver
	if(Touche() == XK_Escape){ // Si le joueur appuie Echap, le jeu se quitte
	  QuitterPartie(&etatJeu,&etatPartie); 
	}
	else{ // Si il appuie tout autre touche que Echap, le jeu recommence
	  break; // On sort de la boucle
	}
      }
  }
  fclose(fichier); // On enregistre le fichier et on le ferme
  FermerGraphique();
  return EXIT_SUCCESS;
}
#endif /* CONSTANTES.H*/
#endif /* STRUCTURES.H*/
#endif /* JEU.H*/
#endif /* AFFICHAGE.H*/
