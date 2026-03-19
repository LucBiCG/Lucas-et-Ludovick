#pragma once
#include <SFML/Graphics.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

#define NB_COL 7
#define NB_LIG 6
#define TAILLE_CASE 60
#define ESPACEMENT 10

typedef enum { MENU, JEU, VICTOIRE } Etatjeu;

extern int Tableau[NB_COL][NB_LIG];
extern Etatjeu sceneActuelle;
extern int gagnantGlobal;
extern int JoueurActuel;

extern float animY;        
extern int animCol;        
extern int animTargetRow;  
extern int isAnimating;

void dessinerGrille(sfRenderWindow* window, sfRectangleShape* rectangle);
void jouerCoup(int colonne);
int verifierVictoire();


void gererMenu(sfRenderWindow* window, sfEvent event, sfSprite* spriteMenu, sfText* texteIntro);
void gererJeu(sfRenderWindow* window, sfEvent event, sfRectangleShape* carre);
void gererVictoire(sfRenderWindow* window, sfEvent event, sfText* texteVictoire);
void gererJeu(sfRenderWindow* window, sfEvent event, sfRectangleShape* carre, sfSprite* sRose, sfSprite* sBleue);