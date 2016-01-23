int DirectionSerpent(int direction) ;
int MettrePause();
Coordonnees DeplacerSerpent(int carre,int direction, Coordonnees* serpent, int tailleSerpent);
void AfficherSerpent(Coordonnees* serpent, int tailleSerpent, int carre, Coordonnees queue);
int CreerPomme(int carre, Pomme* tabPomme, Obstacles* tabObstacle, int tailleSerpent, Coordonnees* serpent);
void CreerObstacles(int carre, Obstacles* tabObstacle);
int VerifieManger(int* score,Coordonnees tete,Pomme* tabPomme, int tailleSerpent,int carre);
