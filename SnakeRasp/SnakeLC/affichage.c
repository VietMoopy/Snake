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

void NettoyerEcran(){
  ChoisirCouleurDessin(CouleurParNom("white"));
  RemplirRectangle(0,0,NB_PIXEL_X_JEU,NB_PIXEL_Y_JEU);
}
 
void AfficherTemps(int seconde, int minute, int carre) // Fonction qui affiche le temps
{
  char tempsTab[6] = {};
  sprintf(tempsTab,"%02d:%02d ",minute,seconde);
  ChoisirCouleurDessin(CouleurParNom("black"));
  RemplirRectangle(0,NB_PIXEL_Y_JEU,500,54);
  ChoisirCouleurDessin(CouleurParNom("white"));
  EcrireTexte(30,590,tempsTab,2);
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



#endif /* CONSTANTES.H*/
#endif /* STRUCTURES.H*/
#endif /* JEU.H*/
#endif /* AFFICHAGE.H*/
