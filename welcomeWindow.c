#include "welcomeWindow.h"

int welcomeWindow()
{
    sfRenderWindow* welcomeWindow = managerCreateWindow(L"Wyścigi samochodowe",800,600,true,1);
    if (welcomeWindow == NULL)
        return 1;
    unsigned int xSize = 800, ySize = 600;
    sfVideoMode mode = {xSize, ySize, 32};
    sfRenderWindow* window;
    sfTexture* texture;
    sfSprite* sprite;
    sfFont* font;
    sfText* text;
    sfMusic* music;
    sfEvent event;

    /* Set a title of the window in Unicode (with PL characters) */
    const wchar_t titlePL[] = L"Wyścigi samochodowe";
    const sfUint32 *ptrUnicodeTitle = (const sfUint32 *) &titlePL;

    /* Create the main window */
    window = sfRenderWindow_createUnicode(mode, ptrUnicodeTitle, sfClose, NULL);
    if (!window)
        return 1;

    /* Center the window */
    sfVector2i windowPos;
    sfVideoMode screenMode;
    screenMode = sfVideoMode_getDesktopMode();
    windowPos.x = screenMode.width/2 - xSize/2;
    windowPos.y = screenMode.height/2 - ySize/2;
    sfRenderWindow_setPosition(window, windowPos);

    /* Load a sprite to display */
    texture = sfTexture_createFromFile("welcome_image.jpeg", NULL);
    if (!texture)
        return 1;
    sprite = sfSprite_create();
    sfSprite_setTexture(sprite, texture, sfTrue);

    /* Create a graphical text (in Unicode) to display */
    font = sfFont_createFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
    if (!font)
        return 1;
    text = sfText_create();
    const wchar_t stringPL[] = L"Kliknij, aby rozpocząć wyścig!";
    const sfUint32 *ptrUnicodeString = (const sfUint32 *) &stringPL;
    sfText_setUnicodeString(text, ptrUnicodeString);
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 50);

    /* Center the text */
    sfFloatRect textRect = sfText_getLocalBounds(text);
    sfVector2f textPos;
    textPos.x = (xSize - textRect.width) /2;
    textPos.y = ySize/3;
    sfText_setPosition(text, textPos);

    /* Load a music to play */
    music = sfMusic_createFromFile("welcome_music.ogg");
    if (!music)
        return 1;

    /* Play the music */
    sfMusic_play(music);

    /* Start the game loop */
    while (sfRenderWindow_isOpen(window))
    {
        /* Process events */
        while (sfRenderWindow_pollEvent(window, &event))
        {
            /* Close window : exit */
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }

        /* Clear the screen */
        sfRenderWindow_clear(window, sfBlack);

        /* Draw the sprite */
        sfRenderWindow_drawSprite(window, sprite, NULL);

        /* Draw the text */
        sfRenderWindow_drawText(window, text, NULL);

        /* Update the window */
        sfRenderWindow_display(window);

        /* Close the window if pressed */
        if(sfMouse_isButtonPressed(sfMouseLeft) ){
            /* Check if mouse is inside the window */
            sfVector2i mousePos = sfMouse_getPosition((const sfWindow *) window);
            if(mousePos.x > 0.0 && mousePos.x < xSize && mousePos.y > 0.0 && mousePos.y < ySize )
                sfRenderWindow_close(window);
        }

    }

    /* Cleanup resources */
    sfMusic_destroy(music);
    sfText_destroy(text);
    sfFont_destroy(font);
    sfSprite_destroy(sprite);
    sfTexture_destroy(texture);
    sfRenderWindow_destroy(window);

    return 0;
}
