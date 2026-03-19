#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include"dependance.h"

int JoueurActuel = 1;
int Tableau[NB_COL][NB_LIG] = { 0 };

void dessinerGrille(sfRenderWindow* window, sfRectangleShape* rectangle) {
    for (int i = 0; i < NB_COL; i++) {
        for (int j = 0; j < NB_LIG; j++) {

            // pos
            sfVector2f pos = {
                i * (TAILLE_CASE + ESPACEMENT) + 20,
                j * (TAILLE_CASE + ESPACEMENT) + 20
            };
            sfRectangleShape_setPosition(rectangle, pos);

            // couleur 
            if (Tableau[i][j] == 0) // Vide
                sfRectangleShape_setFillColor(rectangle, sfColor_fromRGB(40, 40, 40));
            else if (Tableau[i][j] == 1) // 1 R
                sfRectangleShape_setFillColor(rectangle, sfRed);
            else if (Tableau[i][j] == 2) // 2 J
                sfRectangleShape_setFillColor(rectangle, sfYellow);

            sfRenderWindow_drawRectangleShape(window, rectangle, NULL);
        }
    }
}
void jouerCoup(int colonne) {
    // parcour colonne 
    for (int j = NB_LIG - 1; j >= 0; j--) {
        if (Tableau[colonne][j] == 0) { 
            Tableau[colonne][j] = JoueurActuel; 

            //change joueur
            JoueurActuel = (JoueurActuel == 1) ? 2 : 1;
            return; 
        }
    }
}
int verifierVictoire() {
    // 1. Horiz
    for (int j = 0; j < NB_LIG; j++) {
        for (int i = 0; i < NB_COL - 3; i++) {
            if (Tableau[i][j] != 0 &&
                Tableau[i][j] == Tableau[i + 1][j] &&
                Tableau[i][j] == Tableau[i + 2][j] &&
                Tableau[i][j] == Tableau[i + 3][j]) {
                return Tableau[i][j];
            }
        }
    }

    // 2. Verti
    for (int i = 0; i < NB_COL; i++) {
        for (int j = 0; j < NB_LIG - 3; j++) {
            if (Tableau[i][j] != 0 &&
                Tableau[i][j] == Tableau[i][j + 1] &&
                Tableau[i][j] == Tableau[i][j + 2] &&
                Tableau[i][j] == Tableau[i][j + 3]) {
                return Tableau[i][j];
            }
        }
    }

    // 3. Diagonale descendante 
    for (int i = 0; i < NB_COL - 3; i++) {
        for (int j = 0; j < NB_LIG - 3; j++) {
            if (Tableau[i][j] != 0 &&
                Tableau[i][j] == Tableau[i + 1][j + 1] &&
                Tableau[i][j] == Tableau[i + 2][j + 2] &&
                Tableau[i][j] == Tableau[i + 3][j + 3]) {
                return Tableau[i][j];
            }
        }
    }

    // 4. Diagonale montante 
    for (int i = 0; i < NB_COL - 3; i++) {
        for (int j = 3; j < NB_LIG; j++) {
            if (Tableau[i][j] != 0 &&
                Tableau[i][j] == Tableau[i + 1][j - 1] &&
                Tableau[i][j] == Tableau[i + 2][j - 2] &&
                Tableau[i][j] == Tableau[i + 3][j - 3]) {
                return Tableau[i][j];
            }
        }
    }

    return 0; 
}


// --- SCÈNE MENU ---
void gererMenu(sfRenderWindow* window, sfEvent event, sfSprite* spriteMenu,sfText* texteIntro) {
    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed) sfRenderWindow_close(window);
        if (event.type == sfEvtMouseButtonPressed) sceneActuelle = JEU;
    }

    sfRenderWindow_clear(window, sfBlack);

    //image de fond
    sfRenderWindow_drawSprite(window, spriteMenu, NULL);
    

    char message[50];
    sprintf(message, "PUISSSANCE \n       4 !");
    sfText_setString(texteIntro, message);

    //texte
    sfVector2f posTexte = { 0, 75 };
    sfText_setPosition(texteIntro, posTexte);

    //texte
    sfRenderWindow_drawText(window, texteIntro, NULL);

    sfRenderWindow_display(window);
}



// --- SCÈNE JEU ---
void gererJeu(sfRenderWindow* window, sfEvent event, sfRectangleShape* carre) {
    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed) sfRenderWindow_close(window);

        if (event.type == sfEvtMouseButtonPressed && event.mouseButton.button == sfMouseLeft) {
            int col = (event.mouseButton.x - 20) / (TAILLE_CASE + ESPACEMENT);
            if (col >= 0 && col < NB_COL) {
                jouerCoup(col);

                int resultat = verifierVictoire();
                if (resultat != 0) {
                    gagnantGlobal = resultat;
                    sceneActuelle = VICTOIRE; 
                }
            }
        }
    }

    sfRenderWindow_clear(window, sfColor_fromRGB(54, 19, 191));
    dessinerGrille(window, carre);
    sfRenderWindow_display(window);
}



// --- SCÈNE VICTOIRE ---
void gererVictoire(sfRenderWindow* window, sfEvent event, sfText* texteVictoire) {
    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed) sfRenderWindow_close(window);
        if (event.type == sfEvtMouseButtonPressed) {
            
            for (int i = 0; i < NB_COL; i++) for (int j = 0; j < NB_LIG; j++) Tableau[i][j] = 0;
            sceneActuelle = MENU;
        }
    }

    
    char message[50];
    sprintf(message, "Joueur %d a Gagne !", gagnantGlobal);
    sfText_setString(texteVictoire, message);

    //texte
    sfVector2f posTexte = { 100, 200 };
    sfText_setPosition(texteVictoire, posTexte);

    sfColor couleurFond = (gagnantGlobal == 1) ? sfRed : sfYellow;
    sfRenderWindow_clear(window, couleurFond);

    //texte
    sfRenderWindow_drawText(window, texteVictoire, NULL);

    sfRenderWindow_display(window);
}