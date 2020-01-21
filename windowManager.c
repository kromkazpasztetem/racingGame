#include "headers.h"

mWindowInfo mInitInfo(sfRenderWindow* window, sfTexture* texture, sfSprite* sprite){
    mWindowInfo newInfo;
    if ( (newInfo = (mWindowInfo)malloc ( sizeof(struct managerWindowInfo) )) == NULL )
        return false;
    newInfo->window = window;
    newInfo->backgroundSprite = sprite;
    newInfo->backgroundTexture = texture;
    return newInfo;
}

mWindowInfo mCreateWindow (const wchar_t titlePL[], sfVector2u windowSize, sfBool center, uint backgroundID){
    sfRenderWindow* window;
    sfTexture* texture;
    sfSprite* sprite;

    /* Set a size of the window */
    sfVideoMode screenMode;
    screenMode = sfVideoMode_getDesktopMode();
    if(windowSize.x == 0){
        windowSize.x = screenMode.width;
        windowSize.y = screenMode.height;
    }
    sfVideoMode mode = {windowSize.x, windowSize.y, 32};

    /* Set a title of the window in Unicode (with PL characters) */
    const sfUint32 *ptrUnicodeTitle = (const sfUint32 *) &titlePL;

    /* Create the main window */
    window = sfRenderWindow_createUnicode(mode, ptrUnicodeTitle, sfClose, NULL);
    if (!window)
        return NULL;

    /* Center the window */
    sfVector2i windowPos;
    windowPos.x = (screenMode.width - windowSize.x)/2;
    windowPos.y = (screenMode.height - windowSize.y)/2;
    sfRenderWindow_setPosition(window, windowPos);

    /* Draw background */
    char backgroundName [50];
    sprintf(backgroundName,"./images/background%d.png", backgroundID);
    texture = sfTexture_createFromFile(backgroundName, NULL);
    if (!texture)
        return NULL;
    sprite = sfSprite_create();
    sfSprite_setTexture(sprite, texture, sfTrue);

    return mInitInfo(window, texture, sprite);
}
