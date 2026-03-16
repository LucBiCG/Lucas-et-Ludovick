#pragma once
#include <SFML/Graphics.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

// On définit des constantes pour faciliter les modifications plus tard
#define NB_COL 7
#define NB_LIG 6
#define TAILLE_CASE 60
#define ESPACEMENT 10

// Ton tableau global (le 'extern' permet d'éviter les erreurs de double définition)
extern int Tableau[NB_COL][NB_LIG];

// Prototype de la fonction qui va afficher la grille
void dessinerGrille(sfRenderWindow* window, sfRectangleShape* rectangle);

extern int JoueurActuel;

void jouerCoup(int colonne);