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
