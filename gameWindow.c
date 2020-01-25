#include "headers.h"
#define MAPSIZE_X 1600
#define MAPSIZE_Y 900
#define RADIUS 150
#define TEXT_MAXSIZE 100

int gameWindow(){
    sfVector2u windowSize;
    windowSize.x = 0;
    mWindowInfo gameWindowInfo = mCreateWindow(L"Trwa wyścig - Wyścigi samochodowe", windowSize, sfTrue, "background2");
    sfRenderWindow* window2 = gameWindowInfo->window;
    sfSprite* backgroundSprite = gameWindowInfo->backgroundSprite;
    windowSize = gameWindowInfo->windowSize;
    sfRenderWindow_setKeyRepeatEnabled(window2, sfFalse);


    if (window2 == NULL)
        return 1;
    sfFont* font;
    sfText* text;
    //sfMusic* music;
    sfEvent event;

    // Read a track from file as a 0-1 table
    FILE* binaryFile = fopen( "binaryTrack.txt", "r");
    if( binaryFile == NULL ){
        return 1;
    }
    sfVector2i binaryMapSize;
    binaryMapSize.x = MAPSIZE_X;
    binaryMapSize.y = MAPSIZE_Y;
    char binaryMap[binaryMapSize.x][binaryMapSize.y];
    for(int y=0; y<binaryMapSize.y; y++){
        for(int x=0; x<binaryMapSize.x; x++){
            binaryMap[x][y] = getc(binaryFile) - '0';
        }
        getc(binaryFile);
        getc(binaryFile);
        //putc('\n', testFile);
    }
    fclose(binaryFile);
    float scale = (float) (binaryMapSize.x)/(float) (windowSize.x);

    sfSprite* car1 = mCreateSprite("car1", sfTrue);
    sfSprite* car2 = mCreateSprite("car2", sfTrue);
    sfFloatRect sizeCarTemp = sfSprite_getLocalBounds(car1);
    sfVector2f sizeCar;
    sizeCar.x = sizeCarTemp.width;
    sizeCar.y = sizeCarTemp.height;

    sfVector2f car1pos;
    car1pos.x = 850;
    car1pos.y = 758;
    sfVector2f car2pos;
    car2pos.x = 850;
    car2pos.y = 800;
    sfSprite_setRotation(car1, 270);
    sfSprite_setRotation(car2, 270);

    sfCircleShape* circle1 = mCircle(RADIUS, sfCyan);
    sfCircleShape* circle2 = mCircle(RADIUS, sfYellow);

    // Draw the text
    font = sfFont_createFromFile("./fonts/font1.otf");
    if (!font)
        return 1;
    text = sfText_create();
    char string[TEXT_MAXSIZE];
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, TEXT_MAXSIZE);

    sfBool activeCar1 = sfTrue;
    int clicks = 0;
    sfBool mouseHeld = sfFalse;


    // Start the game loop
    while (sfRenderWindow_isOpen(window2))
    {
        // Save a mouse position
        sfVector2i mousePosI = sfMouse_getPosition((const sfWindow *) window2);
        sfVector2f mousePosF;
        mousePosF.x = (float) mousePosI.x;
        mousePosF.y = (float) mousePosI.y;

        // Process events
        while (sfRenderWindow_pollEvent(window2, &event))
        {
            // Close window : exit
            if (event.type == sfEvtClosed){
                sfRenderWindow_close(window2);
                return 0;
            }
        }


        // Capture only one signal
        if(sfMouse_isButtonPressed(sfMouseLeft)) {
            if(!mouseHeld){
                mouseHeld = sfTrue;

                // Check which car was clicked
                if (insideSprite(mousePosF, car1pos, sizeCar) && activeCar1) {
                    //clicks++;

                } else if (insideSprite(mousePosF, car2pos, sizeCar) && !activeCar1) {

                }
                if (mInsideCircle(car1pos, RADIUS, mousePosF))
                    clicks++;
            }
        } else{
            mouseHeld = sfFalse;
        }

        // Clear the screen
        sfRenderWindow_clear(window2, sfBlack);

        // Draw the sprite
        sfRenderWindow_drawSprite(window2, backgroundSprite, NULL);
        sfSprite_setPosition(car1, car1pos);
        sfSprite_setPosition(car2, car2pos);
        sfRenderWindow_drawSprite(window2, car1, NULL);
        sfRenderWindow_drawSprite(window2, car2, NULL);
        sfCircleShape_setPosition(circle1, car1pos);
        sfCircleShape_setPosition(circle2, car2pos);
        sfRenderWindow_drawCircleShape(window2, circle1, NULL);
        sfRenderWindow_drawCircleShape(window2, circle2, NULL);

        // Print a coordinates of the mouse (temp)
        int onTrack;
        onTrack = binaryMap[mRound(mousePosF.x * scale)][mRound(mousePosF.y * scale)];

        sprintf(string, "x:%d y:%d onTrack:%d clicks:%d", mousePosI.x, mousePosI.y, onTrack, clicks);
        sfText_setString(text, string);
        sfRenderWindow_drawText(window2, text, NULL);

        // Update the window
        sfRenderWindow_display(window2);

    }

    // Cleanup resources
    //sfMusic_destroy(music);
    sfText_destroy(text);
    sfFont_destroy(font);
    sfSprite_destroy(backgroundSprite);
    sfRenderWindow_destroy(window2);
    free(binaryMap);

    return 0;
}