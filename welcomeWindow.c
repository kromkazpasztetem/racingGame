#include "headers.h"


int welcomeWindow(int* trackIDptr){

    // Create window, set title, size, background, declare space for resources
    sfVector2u welcomeWindowSize;
    welcomeWindowSize.x = 800, welcomeWindowSize.y = 600;
    mWindowInfo welcomeWindowInfo = mCreateWindow(L"Wyścigi samochodowe",welcomeWindowSize,sfTrue,0);
    sfRenderWindow* window1 = welcomeWindowInfo->window;
    sfSprite* backgroundSprite = welcomeWindowInfo->backgroundSprite;
    if (window1 == NULL)
        return 1;
    sfFont* font;
    sfText* text;
    sfMusic* music;
    sfEvent event;

    // Create a graphical text (in Unicode) to display
    font = sfFont_createFromFile("./fonts/font1.otf");
    if (!font)
        return 1;
    text = sfText_create();
    sfText_setUnicodeString(text, L"Wybierz tor, aby rozpocząć wyścig!");
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 40);
    sfText_setOutlineThickness(text, 2);
    sfText_setOutlineColor(text, sfBlack);

    // Center the text
    sfFloatRect textRect = sfText_getLocalBounds(text);
    sfVector2f textPos;
    textPos.x = (welcomeWindowSize.x - textRect.width) /2;
    textPos.y = welcomeWindowSize.y/20;
    sfText_setPosition(text, textPos);

    // Create buttons
    sfSprite* logo1 = mCreateSprite("logo1", sfTrue);
    sfSprite* logo2 = mCreateSprite("logo2", sfTrue);
    sfSprite* logo3 = mCreateSprite("logo3", sfTrue);

    // Set buttons positions
    sfVector2f logo1pos, logo2pos, logo3pos;
    logo1pos.x = welcomeWindowInfo->windowSize.x/2;
    logo2pos.x = logo1pos.x;
    logo3pos.x = logo1pos.x;
    logo1pos.y = 175;
    logo2pos.y = logo1pos.y + 160;
    logo3pos.y = logo2pos.y + 160;

    sfSprite_setPosition(logo1, logo1pos);
    sfSprite_setPosition(logo2, logo2pos);
    sfSprite_setPosition(logo3, logo3pos);

    sfFloatRect logoSizeTemp = sfSprite_getLocalBounds(logo1);
    sfVector2f logoSize;
    logoSize.x = logoSizeTemp.width;
    logoSize.y = logoSizeTemp.height;

    // Load a music to play
    music = sfMusic_createFromFile("./music/welcomeMusic.ogg");
    if (!music)
        return 1;
    sfMusic_setLoop(music, sfTrue);

    // Play the music
    sfMusic_play(music);

    // Start the game loop
    while (sfRenderWindow_isOpen(window1))
    {
        sfVector2i mousePosI = sfMouse_getPosition((const sfWindow *) welcomeWindowInfo->window);
        sfVector2f mousePosF;
        mousePosF.x = (float) mousePosI.x;
        mousePosF.y = (float) mousePosI.y;

        // Process events
        while (sfRenderWindow_pollEvent(window1, &event))
        {
            // Close window : exit
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window1);
            if (event.type == sfEvtMouseButtonPressed){

                // Check which button was pressed
                if(mInsideSprite(mousePosF, logo1pos, logoSize) ){
                    *trackIDptr = 1;
                    sfRenderWindow_close(window1);
                } else if(mInsideSprite(mousePosF, logo2pos, logoSize) ){
                    *trackIDptr = 2;
                    sfRenderWindow_close(window1);
                } else if(mInsideSprite(mousePosF, logo3pos, logoSize) ){
                    *trackIDptr = 3;
                    sfRenderWindow_close(window1);
                }
            }
        }

        // Clear the screen
        sfRenderWindow_clear(window1, sfBlack);

        // Draw the sprite
        sfRenderWindow_drawSprite(window1, backgroundSprite, NULL);
        sfRenderWindow_drawSprite(window1, logo1, NULL);
        sfRenderWindow_drawSprite(window1, logo2, NULL);
        sfRenderWindow_drawSprite(window1, logo3, NULL);

        // Draw the text
        sfRenderWindow_drawText(window1, text, NULL);

        // Update the window
        sfRenderWindow_display(window1);
    }

    // Cleanup resources
    sfMusic_destroy(music);
    sfText_destroy(text);
    sfFont_destroy(font);
    sfSprite_destroy(backgroundSprite);
    sfRenderWindow_destroy(window1);

    return 0;
}
