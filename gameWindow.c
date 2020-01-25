#include "headers.h"
#define MAPSIZE_X 1600
#define MAPSIZE_Y 850
#define CIRCLE_R 150
#define VECTOR_R 10
#define TEXT_MAXSIZE 100

int gameWindow(){

    // Create window, set title, size, background, declare resources
    sfVector2u windowSize;
    windowSize.x = 0;
    mWindowInfo gameWindowInfo = mCreateWindow(L"Trwa wyścig - Wyścigi samochodowe", windowSize, sfTrue, "background2");
    sfRenderWindow* window2 = gameWindowInfo->window;
    sfSprite* backgroundSprite = gameWindowInfo->backgroundSprite;
    windowSize = gameWindowInfo->windowSize;
    if (window2 == NULL)
        return 1;
    sfFont* font;
    sfText* text;
    //sfMusic* music;
    sfEvent event;

    // Read a racing track from file as a 0-1 table
    FILE* binaryFile = fopen( "binaryTrack.txt", "r");
    if( binaryFile == NULL ){
        return 1;
    }
    int binaryMap[MAPSIZE_X][MAPSIZE_Y];
    for(int y=0; y<MAPSIZE_Y; y++){
        for(int x=0; x<MAPSIZE_X; x++){
            binaryMap[x][y]=0;
            if(getc(binaryFile) - '0' == 1)
                binaryMap[x][y]=1;
        }
        getc(binaryFile);
    }
    fclose(binaryFile);
    float scale = (float) (MAPSIZE_X)/(float) (windowSize.x);

    // Create cars and set default position
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

    sfCircleShape* circle1 = mCircle(CIRCLE_R, sfCyan);
    sfCircleShape* circle2 = mCircle(CIRCLE_R, sfYellow);

    sfVector2f vector2pos;
    vector2pos.x = 100;
    vector2pos.y = 820;
    sfRectangleShape* vector2 = mVectorLine(car2pos, vector2pos, sfMagenta);
    sfCircleShape* vector2head = mVectorTriangle(VECTOR_R, sfMagenta);

    // Draw the text
    font = sfFont_createFromFile("./fonts/font1.otf");
    if (!font)
        return 1;
    text = sfText_create();
    char string[TEXT_MAXSIZE];
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 60);

    // Set booleans to control mouse button
    sfBool activeCar1 = sfTrue;
    sfBool mouseHeld = sfFalse;
    sfBool clickedCar = sfFalse;

    //temp
    int clicks = 0;

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
                if (insideSprite(mousePosF, car1pos, sizeCar) && activeCar1 && !clickedCar) {
                    //clicks++;
                } else if (insideSprite(mousePosF, car2pos, sizeCar) && !activeCar1 && !clickedCar) {

                }
                if (mInsideCircle(car1pos, CIRCLE_R, mousePosF))
                    clicks++;
            }
        } else{
            mouseHeld = sfFalse;
        }

        // Clear the screen
        sfRenderWindow_clear(window2, sfBlack);

        // count rotation and vectors
        float rotation2 = sfRectangleShape_getRotation(vector2);
        sfSprite_setRotation(car2, rotation2);
        sfCircleShape_setRotation(vector2head, rotation2 + 30);

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
        sfRenderWindow_drawRectangleShape(window2, vector2, NULL);
        sfCircleShape_setPosition(vector2head, vector2pos);
        sfRenderWindow_drawCircleShape(window2, vector2head, NULL);

        // Print a coordinates of the mouse (temp)
        int onTrack;
        onTrack = binaryMap[fRound(mousePosF.x * scale)][fRound(mousePosF.y * scale)];
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
    return 0;
}