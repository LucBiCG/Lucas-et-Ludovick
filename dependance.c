#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include"dependance.h"

int JoueurActuel = 1;

int Tableau[NB_COL][NB_LIG] = { 0 };

void dessinerGrille(sfRenderWindow* window, sfRectangleShape* rectangle) {
    for (int i = 0; i < NB_COL; i++) {
        for (int j = 0; j < NB_LIG; j++) {

            // Calcul de la position
            sfVector2f pos = {
                i * (TAILLE_CASE + ESPACEMENT) + 20,
                j * (TAILLE_CASE + ESPACEMENT) + 20
            };
            sfRectangleShape_setPosition(rectangle, pos);

            // Choix de la couleur selon la valeur dans le tableau
            if (Tableau[i][j] == 0) // Vide
                sfRectangleShape_setFillColor(rectangle, sfColor_fromRGB(40, 40, 40));
            else if (Tableau[i][j] == 1) // Joueur 1 (Rouge)
                sfRectangleShape_setFillColor(rectangle, sfRed);
            else if (Tableau[i][j] == 2) // Joueur 2 (Jaune)
                sfRectangleShape_setFillColor(rectangle, sfYellow);

            sfRenderWindow_drawRectangleShape(window, rectangle, NULL);
        }
    }
}
void jouercoup(int colonne) {
    // On parcourt la colonne de bas en haut (de 5 à 0)
    for (int j = NB_LIG - 1; j >= 0; j--) {
        if (Tableau[colonne][j] == 0) { // Si la case est vide
            Tableau[colonne][j] = JoueurActuel; // On place le pion

            // On change de joueur
            JoueurActuel = (JoueurActuel == 1) ? 2 : 1;
            return; // Coup terminé, on sort de la fonction
        }
    }
}