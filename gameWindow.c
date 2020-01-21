#include "headers.h"

int gameWindow(){
    sfVector2u screenSize;
    screenSize.x = 0;
    mWindowInfo gameWindowInfo = mCreateWindow(L"Trwa wyścig - Wyścigi samochodowe", screenSize, sfTrue, 2);
    sfRenderWindow* window2 = gameWindowInfo->window;
    sfTexture* backgroundTexture = gameWindowInfo->backgroundTexture;
    sfSprite* backgroundSprite = gameWindowInfo->backgroundSprite;

    if (window2 == NULL)
        return 1;
    //sfFont* font;
    //sfText* text;
    //sfMusic* music;
    sfEvent event;

    /* Start the game loop */
    while (sfRenderWindow_isOpen(window2))
    {
        /* Process events */
        while (sfRenderWindow_pollEvent(window2, &event))
        {
            /* Close window : exit */
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window2);
        }

        /* Clear the screen */
        sfRenderWindow_clear(window2, sfBlack);

        /* Draw the sprite */
        sfRenderWindow_drawSprite(window2, backgroundSprite, NULL);

        /* Draw the text */
        //sfRenderWindow_drawText(window2, text, NULL);

        /* Update the window */
        sfRenderWindow_display(window2);

    }

    /* Cleanup resources */
    //sfMusic_destroy(music);
    //sfText_destroy(text);
    //sfFont_destroy(font);
    sfSprite_destroy(backgroundSprite);
    sfTexture_destroy(backgroundTexture);
    sfRenderWindow_destroy(window2);

    return 0;
}

