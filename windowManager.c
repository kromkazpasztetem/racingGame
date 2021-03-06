#include "headers.h"

// Initialise struct with window parameters

mWindowInfo mInitInfo(sfRenderWindow* window, sfSprite* sprite, sfVector2u windowSize){
    mWindowInfo newInfo;
    if ( (newInfo = (mWindowInfo)malloc ( sizeof(struct managerWindowInfo) )) == NULL )
        return sfFalse;
    newInfo->window = window;
    newInfo->backgroundSprite = sprite;
    newInfo->windowSize = windowSize;
    return newInfo;
}

// Create the sprite from image

sfSprite* mCreateSprite(char *fileName, sfBool setCenter){
    char spriteName [50];
    sprintf(spriteName,"./images/%s.png", fileName);
    sfTexture* texture = sfTexture_createFromFile(spriteName, NULL);
    if (!texture)
        return NULL;
    sfSprite* sprite = sfSprite_create();
    sfSprite_setTexture(sprite, texture, sfTrue);
    if(setCenter){
        sfFloatRect size = sfSprite_getLocalBounds(sprite);
        sfVector2f center;
        center.x = size.width/2;
        center.y = size.height/2;
        sfSprite_setOrigin(sprite, center);
    }
    return sprite;
}

// Create the window

mWindowInfo mCreateWindow (const sfUint32 *titlePL, sfVector2u windowSize, sfBool center, int backgroundID){
    sfRenderWindow* window;
    sfSprite* sprite;

    // Set a size of the window (0 - maximize window)
    sfVideoMode screenMode;
    screenMode = sfVideoMode_getDesktopMode();
    if(windowSize.x == 0){
        windowSize.x = screenMode.width;
        windowSize.y = screenMode.height;
    }
    sfVideoMode mode = {windowSize.x, windowSize.y, 32};

    // Set a title of the window in Unicode (with PL characters)
    //const sfUint32 *ptrUnicodeTitle = (const sfUint32 *) &titlePL;

    // Create the main window
    window = sfRenderWindow_createUnicode(mode, titlePL, sfClose, NULL);
    if (!window)
        return NULL;

    if(center){
        // Center the window
        sfVector2i windowPos;
        windowPos.x = (screenMode.width - windowSize.x)/2;
        windowPos.y = (screenMode.height - windowSize.y)/2;
        sfRenderWindow_setPosition(window, windowPos);
    }

    // Create background
    char backgroundName [50];
    sprintf(backgroundName,"background%d", backgroundID);
    sprite = mCreateSprite(backgroundName, sfFalse);

    return mInitInfo(window, sprite, windowSize);
}