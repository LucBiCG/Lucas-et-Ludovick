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
float animY = -100.0f;
int animCol = 0;
int animTargetRow = 0;
int isAnimating = 0;

void gererJeu(sfRenderWindow* window, sfEvent event, sfRectangleShape* carre, sfSprite* sRose, sfSprite* sBleue) {

    // 1. GESTION DES ÉVÉNEMENTS (Uniquement si on n'est pas en train d'animer)
    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed) sfRenderWindow_close(window);

        if (!isAnimating && event.type == sfEvtMouseButtonPressed && event.mouseButton.button == sfMouseLeft) {
            int col = (event.mouseButton.x - 20) / (TAILLE_CASE + ESPACEMENT);

            if (col >= 0 && col < NB_COL) {
                // On cherche la ligne d'arrivée
                for (int j = NB_LIG - 1; j >= 0; j--) {
                    if (Tableau[col][j] == 0) {
                        // ON NE REMPLIT PAS LE TABLEAU TOUT DE SUITE
                        // On lance l'animation
                        isAnimating = 1;
                        animCol = col;
                        animTargetRow = j;
                        animY = -50.0f; // Départ au-dessus de l'écran
                        break;
                    }
                }
            }
        }
    }

    // 2. MISE À JOUR DE L'ANIMATION
    if (isAnimating) {
        float vitesseChute = 0.50f; 
        float targetYPixel = animTargetRow * (TAILLE_CASE + ESPACEMENT) + 20;

        if (animY < targetYPixel) {
            animY += vitesseChute; // L'épée descend
        }
        else {
            // L'épée est arrivée !
            Tableau[animCol][animTargetRow] = JoueurActuel; 
            isAnimating = 0; // Animation finie
            JoueurActuel = (JoueurActuel == 1) ? 2 : 1; 

            // On vérifie la victoire après la chute
            int resultat = verifierVictoire();
            if (resultat != 0) {
                gagnantGlobal = resultat;
                sceneActuelle = VICTOIRE;
            }
        }
    }

    // 3. RENDU
    sfRenderWindow_clear(window, sfColor_fromRGB(54, 19, 191));
    dessinerGrille(window, carre);

   
    if (isAnimating) {
        sfSprite* epeeAnim = (JoueurActuel == 1) ? sRose : sBleue;
        sfVector2f pos = { (float)(animCol * (TAILLE_CASE + ESPACEMENT) + 20), animY };
        sfSprite_setPosition(epeeAnim, pos);
        sfRenderWindow_drawSprite(window, epeeAnim, NULL);
    }
    
    else {
        sfVector2i m = sfMouse_getPositionRenderWindow(window);
        int c = (m.x - 20) / (TAILLE_CASE + ESPACEMENT);
        if (c >= 0 && c < NB_COL) {
            sfSprite* epeeHover = (JoueurActuel == 1) ? sRose : sBleue;
            sfVector2f posH = { (float)(c * (TAILLE_CASE + ESPACEMENT) + 20), -10.0f };
            sfSprite_setPosition(epeeHover, posH);
            
            sfSprite_setColor(epeeHover, sfColor_fromRGBA(255, 255, 255, 150));
            sfRenderWindow_drawSprite(window, epeeHover, NULL);
            sfSprite_setColor(epeeHover, sfWhite); 
        }
    }

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