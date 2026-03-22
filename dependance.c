#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include"dependance.h"

int JoueurActuel = 1;
int Tableau[NB_COL][NB_LIG] = { 0 };
int contreIA = 1; 

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
void gererMenu(sfRenderWindow* window, sfEvent event, sfSprite* spriteMenu, sfText* texteIntro) {
    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed) sfRenderWindow_close(window);

        if (event.type == sfEvtKeyPressed) {
            if (event.key.code == sfKeyA) {
                contreIA = 1; 
                sceneActuelle = JEU;
            }
            if (event.key.code == sfKeyP) {
                contreIA = 0; 
                sceneActuelle = JEU;
            }
        }
    }

    sfRenderWindow_clear(window, sfBlack);
    sfRenderWindow_drawSprite(window, spriteMenu, NULL);

    
    sfText_setString(texteIntro, "PUISSANCE 4\n[A] vs IA\n[P] vs AMI");
    sfText_setCharacterSize(texteIntro, 50); 
    sfText_setPosition(texteIntro, (sfVector2f) { 120, 50 });

    sfRenderWindow_drawText(window, texteIntro, NULL);
    sfRenderWindow_display(window);
}



// --- SCÈNE JEU ---
float animY = -100.0f;
int animCol = 0;
int animTargetRow = 0;
int isAnimating = 0;

void gererJeu(sfRenderWindow* window, sfEvent event, sfRectangleShape* carre, sfSprite* sRose, sfSprite* sBleue) {

    // 1. GESTION DES ÉVÉNEMENTS 
    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed) sfRenderWindow_close(window);

        if (!isAnimating && event.type == sfEvtMouseButtonPressed && event.mouseButton.button == sfMouseLeft) {
            int col = (event.mouseButton.x - 20) / (TAILLE_CASE + ESPACEMENT);

            if (col >= 0 && col < NB_COL) {
                
                for (int j = NB_LIG - 1; j >= 0; j--) {
                    if (Tableau[col][j] == 0) {
                        
                        
                        isAnimating = 1;
                        animCol = col;
                        animTargetRow = j;
                        animY = -50.0f; 
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
            animY += vitesseChute; 
        }
        else {
            
            Tableau[animCol][animTargetRow] = JoueurActuel; 
            isAnimating = 0; 
            JoueurActuel = (JoueurActuel == 1) ? 2 : 1; 

           
            int resultat = verifierVictoire();
            if (resultat != 0) {
                gagnantGlobal = resultat;
                sceneActuelle = VICTOIRE;
            }
        }
    }
    // --- LOGIQUE IA ---
    if (contreIA && JoueurActuel == 2 && !isAnimating && sceneActuelle == JEU) {
        tourIA();
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



void tourIA() {
    if (isAnimating) return;

    int colChoisie = -1;

    // 1. ANALYSE
    for (int c = 0; c < NB_COL; c++) {
        for (int l = NB_LIG - 1; l >= 0; l--) {
            if (Tableau[c][l] == 0) {
                Tableau[c][l] = 2; 
                if (verifierVictoire() == 2) colChoisie = c;
                Tableau[c][l] = 0; 
                break;
            }
        }
        if (colChoisie != -1) break;
    }

    // 2. BLOCAGE 
    if (colChoisie == -1) {
        for (int c = 0; c < NB_COL; c++) {
            for (int l = NB_LIG - 1; l >= 0; l--) {
                if (Tableau[c][l] == 0) {
                    Tableau[c][l] = 1; 
                    if (verifierVictoire() == 1) colChoisie = c;
                    Tableau[c][l] = 0;
                    break;
                }
            }
            if (colChoisie != -1) break;
        }
    }

    // 3. HASARD 
    if (colChoisie == -1) {
        do {
            colChoisie = rand() % NB_COL;
        } while (Tableau[colChoisie][0] != 0);
    }

    
    for (int j = NB_LIG - 1; j >= 0; j--) {
        if (Tableau[colChoisie][j] == 0) {
            isAnimating = 1;
            animCol = colChoisie;
            animTargetRow = j;
            animY = animY - 100.0f;
            break;
        }
    }
}