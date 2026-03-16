#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include"dependance.h"
int main(void)
{
    sfVideoMode mode = { 550, 500, 32 }; // Fenêtre un peu plus large
    sfRenderWindow* window = sfRenderWindow_create(mode, "Puissance 4", sfClose, NULL);
    sfEvent event;

    // On prépare l'objet rectangle UNE SEULE FOIS pour les performances
    sfRectangleShape* carre = sfRectangleShape_create();
    sfVector2f size = { TAILLE_CASE, TAILLE_CASE };
    sfRectangleShape_setSize(carre, size);
    sfRectangleShape_setOutlineThickness(carre, 2);
    sfRectangleShape_setOutlineColor(carre, sfWhite);

    if (!window)
    {
        return -1;
    }

    srand((unsigned int)time(NULL));

    /* Start the game loop */
    while (sfRenderWindow_isOpen(window))
    {
        
        /* Process events */
        while (sfRenderWindow_pollEvent(window, &event))
        {
            
            /* Close window : exit */
            if (event.type == sfEvtClosed)
            {
                sfRenderWindow_close(window);
            }
            while (sfRenderWindow_pollEvent(window, &event)) {
                if (event.type == sfEvtClosed) {
                    sfRenderWindow_close(window);
                }

                // Détection du clic gauche
                if (event.type == sfEvtMouseButtonPressed && event.mouseButton.button == sfMouseLeft) {
                    int x = event.mouseButton.x;

                    // On calcule l'index de la colonne en fonction des pixels
                    // (x - décalage_gauche) / (taille_case + espacement)
                    int col = (x - 20) / (TAILLE_CASE + ESPACEMENT);

                    if (col >= 0 && col < NB_COL) {
                        jouerCoup(col);
                    }
                }
            }

        }
        sfColor Blue = sfColor_fromRGB(54, 19, 191);

        /* Clear the screen */
        sfRenderWindow_clear(window, Blue);

        dessinerGrille(window, carre);
        /* Update the window */
        sfRenderWindow_display(window);
    }

    /* Cleanup resources */
    sfRectangleShape_destroy(carre);
    sfRenderWindow_destroy(window);

    return 1;
}
