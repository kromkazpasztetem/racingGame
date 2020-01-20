#include "windowManager.h"

sfRenderWindow* managerCreateWindow (const wchar_t titlePL[], uint xSize, uint ySize, sfBool center, uint backgroundID){
    sfRenderWindow* window;
    sfTexture* texture;
    sfSprite* sprite;

    /* Set a size of the window */
    sfVideoMode mode = {xSize, ySize, 32};

    /* Set a title of the window in Unicode (with PL characters) */
    const sfUint32 *ptrUnicodeTitle = (const sfUint32 *) &titlePL;

    /* Create the main window */
    window = sfRenderWindow_createUnicode(mode, ptrUnicodeTitle, sfClose, NULL);
    if (!window)
        return NULL;

    /* Center the window */
    sfVector2i windowPos;
    sfVideoMode screenMode;
    screenMode = sfVideoMode_getDesktopMode();
    windowPos.x = screenMode.width/2 - xSize/2;
    windowPos.y = screenMode.height/2 - ySize/2;
    sfRenderWindow_setPosition(window, windowPos);

    /* Draw background */
    char backgroundName [20];
    sprintf(backgroundName,"background%d.jpeg",backgroundID);
    texture = sfTexture_createFromFile(backgroundName, NULL);
    if (!texture)
        return NULL;
    sprite = sfSprite_create();
    sfSprite_setTexture(sprite, texture, sfTrue);

    return window;
}
