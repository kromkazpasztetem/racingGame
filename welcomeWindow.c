#include "headers.h"


int welcomeWindow(){

    // Create window, set title, size, background, declare space for resources
    sfVector2u welcomeWindowSize;
    welcomeWindowSize.x = 800, welcomeWindowSize.y = 600;
    mWindowInfo welcomeWindowInfo = mCreateWindow(L"Wyścigi samochodowe",welcomeWindowSize,sfTrue,"background1");
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
    sfText_setUnicodeString(text, L"Kliknij, aby rozpocząć wyścig!");
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 50);

    // Center the text
    sfFloatRect textRect = sfText_getLocalBounds(text);
    sfVector2f textPos;
    textPos.x = (welcomeWindowSize.x - textRect.width) /2;
    textPos.y = welcomeWindowSize.y/3;
    sfText_setPosition(text, textPos);

    // Load a music to play
    music = sfMusic_createFromFile("./music/welcome_music.ogg");
    if (!music)
        return 1;
    sfMusic_setLoop(music, sfTrue);

    // Play the music
    sfMusic_play(music);

    // Start the game loop
    while (sfRenderWindow_isOpen(window1))
    {
        // Process events
        while (sfRenderWindow_pollEvent(window1, &event))
        {
            // Close window : exit
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window1);
            if (event.type == sfEvtMouseButtonPressed){
                sfRenderWindow_close(window1);
            }
        }

        // Clear the screen
        sfRenderWindow_clear(window1, sfBlack);

        // Draw the sprite
        sfRenderWindow_drawSprite(window1, backgroundSprite, NULL);

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
