#include "goodbyeWindow.h"

#include "headers.h"


int goodbyeWindow(sfBool winnerPlayer1){
    // Create window, set title, size, background, declare space for resources
    sfVector2u goodbyeWindowSize;
    goodbyeWindowSize.x = 800, goodbyeWindowSize.y = 600;
    mWindowInfo window3Info = mCreateWindow(L"Wyścigi samochodowe - meta",goodbyeWindowSize,sfTrue,0);
    if (window3Info->window == NULL)
        return 1;
    sfFont* font;
    sfText *text, *text2, *text3;
    sfMusic* music;
    sfEvent event;

    // Create a graphical text (in Unicode) to display
    font = sfFont_createFromFile("./fonts/font1.otf");
    if (!font)
        return 1;
    text = sfText_create();
    sfText_setUnicodeString(text, L"Wygrywa...");
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 60);
    sfText_setOutlineThickness(text, 3);
    sfText_setOutlineColor(text, sfBlack);

    // Set text position
    sfFloatRect textRect = sfText_getLocalBounds(text);
    sfVector2f textPos;
    textPos.x = (window3Info->windowSize.x - textRect.width) /2;
    textPos.y = window3Info->windowSize.y/8;
    sfText_setPosition(text, textPos);

    text2 = sfText_create();
    if(winnerPlayer1){
        sfText_setUnicodeString(text2, L"Gracz 1");
        sfText_setColor(text2, sfBlue);
    }else{
        sfText_setUnicodeString(text2, L"Gracz 2");
        sfText_setColor(text2, sfYellow);
    }
    sfText_setOutlineColor(text2, sfBlack);
    sfText_setFont(text2, font);
    sfText_setCharacterSize(text2, 120);
    sfText_setOutlineThickness(text2, 3);

    // Set text2 position
    textRect = sfText_getLocalBounds(text2);
    textPos.x = (window3Info->windowSize.x - textRect.width) /2;
    textPos.y = window3Info->windowSize.y/3;
    sfText_setPosition(text2, textPos);

    text3 = sfText_create();
    sfText_setUnicodeString(text3, L"Kliknij, aby zakończyć");
    sfText_setFont(text3, font);
    sfText_setCharacterSize(text3, 40);
    sfText_setOutlineThickness(text3, 3);
    sfText_setOutlineColor(text3, sfBlack);

    // Set text3 position
    textRect = sfText_getLocalBounds(text3);
    textPos.x = (window3Info->windowSize.x - textRect.width) /2;
    textPos.y = window3Info->windowSize.y*3/4;
    sfText_setPosition(text3, textPos);

    // Load a music to play
    music = sfMusic_createFromFile("./music/welcomeMusic.ogg");
    if (!music)
        return 1;
    sfMusic_setLoop(music, sfTrue);

    // Play the music
    sfMusic_play(music);

    // Start the game loop
    while (sfRenderWindow_isOpen(window3Info->window))
    {
        sfVector2i mousePosI = sfMouse_getPosition((const sfWindow *) window3Info->window);
        sfVector2f mousePosF;
        mousePosF.x = (float) mousePosI.x;
        mousePosF.y = (float) mousePosI.y;

        // Process events
        while (sfRenderWindow_pollEvent(window3Info->window, &event))
        {
            // Close window : exit
            if (event.type == sfEvtClosed || event.type == sfEvtMouseButtonPressed)
                sfRenderWindow_close(window3Info->window);
        }

        // Clear the screen
        sfRenderWindow_clear(window3Info->window, sfBlack);

        // Draw the sprite
        sfRenderWindow_drawSprite(window3Info->window, window3Info->backgroundSprite, NULL);

        // Draw the text
        sfRenderWindow_drawText(window3Info->window, text, NULL);
        sfRenderWindow_drawText(window3Info->window, text2, NULL);
        sfRenderWindow_drawText(window3Info->window, text3, NULL);

        // Update the window
        sfRenderWindow_display(window3Info->window);
    }

    // Cleanup resources
    sfMusic_destroy(music);
    sfText_destroy(text);
    sfText_destroy(text2);
    sfText_destroy(text3);
    sfFont_destroy(font);
    sfSprite_destroy(window3Info->backgroundSprite);
    sfRenderWindow_destroy(window3Info->window);

    return 0;
}
