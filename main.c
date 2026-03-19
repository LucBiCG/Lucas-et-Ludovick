#include <SFML/Audio.h>
#include <SFML/Graphics.h>
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

    while (sfRenderWindow_isOpen(window)) {
        

        switch (sceneActuelle) {
        case MENU:
            gererMenu(window, event, spriteMenu, texteIntro);
            break;
        case JEU:
            gererJeu(window, event, carre);
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

    return 0;
}
