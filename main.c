#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
<<<<<<< HEAD
#include <stdlib.h>
#include <time.h>
#include <stdio.h> 


// IA
int jouerIA(int grille[6][7])
{
    int colonne;

    while (1)
    {
        colonne = rand() % 7; // colonne aléatoire

        // vérifier si la colonne n'est pas pleine
        if (grille[0][colonne] == 0)
            return colonne;
    }
}

// Condition Victoire
int verifierVictoire(int grille[6][7]) {

    // Horizontal
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (grille[i][j] != 0 &&
                grille[i][j] == grille[i][j + 1] &&
                grille[i][j] == grille[i][j + 2] &&
                grille[i][j] == grille[i][j + 3])
                return grille[i][j];
        }
    }

    // Vertical
    for (int j = 0; j < 7; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            if (grille[i][j] != 0 &&
                grille[i][j] == grille[i + 1][j] &&
                grille[i][j] == grille[i + 2][j] &&
                grille[i][j] == grille[i + 3][j])
                return grille[i][j];
        }
    }

    // Diagonale ↘
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (grille[i][j] != 0 &&
                grille[i][j] == grille[i + 1][j + 1] &&
                grille[i][j] == grille[i + 2][j + 2] &&
                grille[i][j] == grille[i + 3][j + 3])
                return grille[i][j];
        }
    }

    // Diagonale ↗
    for (int i = 3; i < 6; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (grille[i][j] != 0 &&
                grille[i][j] == grille[i - 1][j + 1] &&
                grille[i][j] == grille[i - 2][j + 2] &&
                grille[i][j] == grille[i - 3][j + 3])
                return grille[i][j];
        }
    }

    return 0; // pas de gagnant
}

int main(void)
{
    sfVideoMode mode = { 500, 440, 32 };
    sfRenderWindow* window;
    sfEvent event;

    int joueur = 1;
    int grille[6][7] = { 0 }; // tableau du jeu

    window = sfRenderWindow_create(mode, "Puissance 4", sfClose, NULL);
    if (!window)
        return -1;
   

    srand((unsigned int)time(NULL));

    while (sfRenderWindow_isOpen(window))
    {
        while (sfRenderWindow_pollEvent(window, &event))
        {
           
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);

            if (event.type == sfEvtMouseButtonPressed && joueur == 1)
            {
                int x = event.mouseButton.x;
                int colonne = x / 70;

                if (colonne >= 0 && colonne < 7)
                {
                    for (int i = 5; i >= 0; i--)
                    {
                        if (grille[i][colonne] == 0)
                        {
                            grille[i][colonne] = joueur;

                            int gagnant = verifierVictoire(grille);

                            if (gagnant != 0)
                            {
                                printf("Joueur %d gagne !\n", gagnant);
                                sfRenderWindow_close(window);
                            }

                            joueur = 2; // tour IA
                            break;
                        }
                    }
                }
            }
        } if (joueur == 2)
        {
            

            sfSleep(sfMilliseconds(300));

            int colonne = jouerIA(grille);

            for (int i = 5; i >= 0; i--)
            {
                if (grille[i][colonne] == 0)
                {
                    grille[i][colonne] = joueur;

                    int gagnant = verifierVictoire(grille);

                    if (gagnant != 0)
                    {
                        printf("Joueur %d gagne !\n", gagnant);
                        sfRenderWindow_close(window);
                    }

                    joueur = 1; // retour joueur
                    
                    break;
                }
            }
        }
           
    

        sfColor fondgrille = sfColor_fromRGB(54, 19, 191);
        sfRenderWindow_clear(window, fondgrille);

        /*grille */
        sfCircleShape* pion = sfCircleShape_create();
        sfCircleShape_setRadius(pion, 30);
        sfCircleShape_setFillColor(pion, sfWhite);

        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                sfVector2f position;
                position.x = j * 70 + 10;
                position.y = i * 70 + 10;
               
                if (grille[i][j] == 1)
                    sfCircleShape_setFillColor(pion, sfRed);
                else if (grille[i][j] == 2)
                    sfCircleShape_setFillColor(pion, sfYellow);
                else
                    sfCircleShape_setFillColor(pion, sfWhite);

                sfCircleShape_setPosition(pion, position);
                sfRenderWindow_drawCircleShape(window, pion, NULL);
            }
        }

        sfCircleShape_destroy(pion);

        sfRenderWindow_display(window);
    }

    sfRenderWindow_destroy(window);

   
    return 0;
}
=======
#include "dependance.h"

int gagnantGlobal = 0;
Etatjeu sceneActuelle = MENU;

int main(void) {
    sfVideoMode mode = { 550, 500, 32 };
    sfRenderWindow* window = sfRenderWindow_create(mode, "Puissance 4", sfClose, NULL);
    sfEvent event = { 0 }; 

    if (!window) return -1;

    sfRectangleShape* carre = sfRectangleShape_create();
    sfVector2f size = { TAILLE_CASE, TAILLE_CASE };
    sfRectangleShape_setSize(carre, size);
    sfRectangleShape_setOutlineThickness(carre, 2);
    sfRectangleShape_setOutlineColor(carre, sfWhite);

    srand((unsigned int)time(NULL));

    // Image
    sfTexture* textureMenu = sfTexture_createFromFile("C:/Users/Lucas/Documents/GitHub/Puissance4/Malenia.jpg", NULL);
    sfSprite* spriteMenu = sfSprite_create();
    sfSprite_setTexture(spriteMenu, textureMenu, sfTrue);

    sfFont* font = sfFont_createFromFile("C:/Users/Lucas/Documents/GitHub/Puissance4/Black Rose Studio.ttf");
    sfText* texteVictoire = sfText_create();
    sfText_setFont(texteVictoire, font);
    sfText_setCharacterSize(texteVictoire, 50);
    sfText_setFillColor(texteVictoire, sfWhite); 

    sfText* texteIntro = sfText_create();
    sfText_setFont(texteIntro, font);
    sfText_setCharacterSize(texteIntro, 90);
    sfText_setFillColor(texteIntro, sfColor_fromRGB(246, 184, 72));

   
    sfTexture* tRose = sfTexture_createFromFile("C:/Users/Lucas/Documents/GitHub/Puissance4/Sword1.png", NULL);
    sfSprite* sRose = sfSprite_create();
    sfSprite_setTexture(sRose, tRose, sfTrue);

    sfTexture* tBleue = sfTexture_createFromFile("C:/Users/Lucas/Documents/GitHub/Puissance4/Sword2.png", NULL);
    sfSprite* sBleue = sfSprite_create();
    sfSprite_setTexture(sBleue, tBleue, sfTrue);

    
    sfVector2f scaleSword = { 0.15f, 0.15f };
    
    sfSprite_setScale(sRose, scaleSword);
    sfSprite_setScale(sBleue, scaleSword);
    







    while (sfRenderWindow_isOpen(window)) {
        

        switch (sceneActuelle) {
        case MENU:
            gererMenu(window, event, spriteMenu, texteIntro);
            break;
        case JEU:
            gererJeu(window, event, carre, sBleue, sRose);
            break;
        case VICTOIRE:
            gererVictoire(window, event, texteVictoire);
            break;
        }
    }

    // clean
    sfSprite_destroy(spriteMenu);
    sfTexture_destroy(textureMenu);
    sfText_destroy(texteVictoire);
    sfFont_destroy(font);
    sfRectangleShape_destroy(carre);
    sfRenderWindow_destroy(window);

    sfSprite_destroy(sRose);
    sfTexture_destroy(tRose);

    sfSprite_destroy(sBleue);
    sfTexture_destroy(tBleue);
    return 0;
}
>>>>>>> LUCAS
