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

void NettoyerEcran(){ // Remplit la fenetre de blanc
  ChoisirCouleurDessin(CouleurParNom("white"));
  RemplirRectangle(0,0,NB_PIXEL_X_JEU,NB_PIXEL_Y_JEU);
}
 
void AfficherTemps(int seconde, int minute, int carre) // Fonction qui affiche le temps
{
  char tempsTab[6] = {};
  sprintf(tempsTab,"%02d:%02d ",minute,seconde);
  ChoisirCouleurDessin(CouleurParNom("black"));
  RemplirRectangle(0,NB_PIXEL_Y_JEU,420,54);
  ChoisirCouleurDessin(CouleurParNom("white"));
  EcrireTexte(30,590,tempsTab,2);
} 

void AfficherScore(int score) // Fonction qui affiche le score
{ 
  char scoreTab[8] = {'0','0','0','0','0','0','0','\0'};
  sprintf(scoreTab,"%07d",score);
  ChoisirCouleurDessin(CouleurParNom("black"));
  RemplirRectangle(420,NB_PIXEL_Y_JEU,420,54);
  ChoisirCouleurDessin(CouleurParNom("white"));
  EcrireTexte(730,590,scoreTab,2);
}

void AfficherGameOver(){ // Affiche que la partie est perdue et les choix possibles : Recommencer ou Quitter
  ChoisirCouleurDessin(CouleurParNom("red"));
  EcrireTexte(340,260,"Vous avez perdu !",2);	
  EcrireTexte(120,290,"Appuyez sur n'importe quelle touche pour recommencer",2);
  EcrireTexte(260,320,"Appuyez sur Echap pour quitter",2);
}


#endif /* CONSTANTES.H*/
#endif /* STRUCTURES.H*/
#endif /* JEU.H*/
#endif /* AFFICHAGE.H*/
