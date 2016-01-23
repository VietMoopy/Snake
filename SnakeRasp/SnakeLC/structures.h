typedef struct Coordonnees Coordonnees;
struct Coordonnees

{
  int x;
  int y;
};

typedef struct EltSerpent EltSerpent;
struct EltSerpent

{
  Coordonnees element;
  EltSerpent* suivant;
  EltSerpent* precedent;
};


typedef struct Serpent Serpent;
struct Serpent

{
  int tailleSerpent;
  EltSerpent* tete;
};

typedef struct Pomme Pomme;
struct Pomme

{
  int x;
  int y;
  int flagP;
};

typedef struct Obstacles Obstacles;
struct Obstacles

{
  int x;
  int y;
};


