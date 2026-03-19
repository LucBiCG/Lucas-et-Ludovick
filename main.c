#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h> 

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

            if (event.type == sfEvtMouseButtonPressed)
            {
                if (event.mouseButton.button == sfMouseLeft)
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
                                    
                                                    ("Joueur %d gagne !\n", gagnant);
                                    sfRenderWindow_close(window); // ou arrêter le jeu
                                }
                                if (joueur == 1)
                                    joueur = 2;
                                else
                                    joueur = 1;

                                break;
                            }
                        }
                    }
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