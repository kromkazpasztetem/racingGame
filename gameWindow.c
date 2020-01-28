#include "headers.h"

#define MAPSIZE_X 1600
#define MAPSIZE_Y 850
#define CIRCLE_R 100
#define SPIKE_R 10
#define ON_TRACK_NERF 2
#define OFF_TRACK_NERF 64


// Create car and initialise default parameters

struct car initCar(int carID, sfColor color){
    struct car newCar;
    char carName [50];
    sprintf(carName,"car%d", carID);
    newCar.image = mCreateSprite(carName, sfTrue);
    newCar.vectorColor = color;
    newCar.circle = mCircle(CIRCLE_R, newCar.vectorColor);
    newCar.vectorSpike = mVectorSpike(SPIKE_R, newCar.vectorColor);
    return newCar;
}

sfBool** readTrack(){

    // Allocate space
    sfBool **binaryMap;
    if (( binaryMap =(sfBool**) malloc( MAPSIZE_X * sizeof( sfBool* ))) == NULL )
        return NULL;
    for(int x=0; x<MAPSIZE_X; x++) {
        if ((binaryMap[x] = (sfBool *) malloc(MAPSIZE_Y * sizeof(sfBool))) == NULL)
            return NULL;
    }

    // Read a racing track from file as a 0-1 table
    FILE* binaryFile = fopen( "binaryTrack.txt", "r");
    if( binaryFile == NULL ){
        return NULL;
    }
    for(int y=0; y<MAPSIZE_Y; y++){
        for(int x=0; x<MAPSIZE_X; x++){
            binaryMap[x][y]=sfTrue;
            if(getc(binaryFile) == '1')
                binaryMap[x][y]=sfFalse;
        }
        getc(binaryFile);
    }
    fclose(binaryFile);

    return binaryMap;
}

void mChangeVector(ptrCar carPtr, sfVector2f mousePos, sfBool** onTrack, sfVector2u windowSize){
    // Count new vector
    sfVector2f newVector;
    newVector.x = (carPtr->endPos.x - carPtr->beginPos.x) + (mousePos.x - carPtr->beginPos.x);
    newVector.y = (carPtr->endPos.y - carPtr->beginPos.y) + (mousePos.y - carPtr->beginPos.y);

    // Divide the vector by integer (just to balance purposes)
    newVector.x/=ON_TRACK_NERF;
    newVector.y/=ON_TRACK_NERF;

    // Count scale of the binary track map
    float scale = (float) (MAPSIZE_X)/(float) (windowSize.x);

    // Count new position of the car and check if it still on the screen
    carPtr->beginPos.x = carPtr->endPos.x + newVector.x;
    if( carPtr->beginPos.x > MAPSIZE_X*scale )
        carPtr->beginPos.x = MAPSIZE_X;
    else if( carPtr->beginPos.x < 0 )
        carPtr->beginPos.x = 0;
    carPtr->beginPos.y = carPtr->endPos.y + newVector.y;
    if( carPtr->beginPos.y > MAPSIZE_Y*scale )
        carPtr->beginPos.y = MAPSIZE_Y;
    else if ( carPtr->beginPos.y <0 )
        carPtr->beginPos.y = 0;

    // Check if the car is on the track
    if(!onTrack[ fRound(carPtr->beginPos.x * scale) ][ fRound(carPtr->beginPos.y * scale) ]){

        // Divide vector by larger integer in case of driving off-track
        newVector.x/=OFF_TRACK_NERF;
        newVector.y/=OFF_TRACK_NERF;
    }

    // Count new position of the vector
    carPtr->endPos = carPtr->beginPos;
    carPtr->endPos.x += newVector.x;
    carPtr->endPos.y += newVector.y;
}

void mRotate(ptrCar carPtr){

    // Create a line of the vector
    carPtr->vectorLine = mVectorLine(carPtr->beginPos, carPtr->endPos, carPtr->vectorColor);
    float angle = 0;

    // Do not rotate if vector is null
    if(carPtr->vectorLine != NULL)
        angle = sfRectangleShape_getRotation(carPtr->vectorLine);

    // Rotate by angle of the vector line
    sfSprite_setRotation(carPtr->image, angle);
    sfCircleShape_setRotation(carPtr->vectorSpike, angle + 30);
}

void mPosition(ptrCar carPtr){

    // Set new position of the car and circle
    sfSprite_setPosition(carPtr->image, carPtr->beginPos);
    sfCircleShape_setPosition(carPtr->circle, carPtr->beginPos);

    // Set new position of the vector if not null
    if(carPtr->vectorLine != NULL){
        sfRectangleShape_setPosition(carPtr->vectorLine, carPtr->beginPos);
        sfCircleShape_setPosition(carPtr->vectorSpike, carPtr->endPos);
    }
}

void mDraw(ptrCar carPtr, sfRenderWindow* gameWindow){

    // Draw the car
    sfRenderWindow_drawSprite(gameWindow, carPtr->image, NULL);

    // Draw the vector if not null
    if(carPtr->vectorLine != NULL){
        sfRenderWindow_drawRectangleShape(gameWindow, carPtr->vectorLine, NULL);
        sfRenderWindow_drawCircleShape(gameWindow, carPtr->vectorSpike, NULL);
    }
}

int gameWindow(){

    // Create window, set title, size, background, declare resources
    sfVector2u windowSize;
    windowSize.x = 0;
    mWindowInfo gameWindowInfo = mCreateWindow(L"Trwa wyścig - Wyścigi samochodowe", windowSize, sfTrue, "background2");
    if (gameWindowInfo->window == NULL)
        return 1;
    //sfFont* font;
    sfMusic* music;
    sfEvent event;
    sfBool** onTrack = readTrack();

    struct car car1 = initCar(1, sfBlue);
    struct car car2 = initCar(2, sfYellow);

    // Create cars
    sfFloatRect sizeCarTemp = sfSprite_getLocalBounds(car1.image);
    sfVector2f sizeCar;
    sizeCar.x = sizeCarTemp.width;
    sizeCar.y = sizeCarTemp.height;

    // Set default position
    car1.beginPos.x = 850;
    car1.beginPos.y= 758;
    car1.endPos = car1.beginPos;
    car2.beginPos.x = 850;
    car2.beginPos.y = 800;
    car2.endPos = car2.beginPos;

    // Load a music to play
    music = sfMusic_createFromFile("./music/game_music.wav");
    if (!music)
        return 1;
    sfMusic_setLoop(music, sfTrue);

    // Play the music
    sfMusic_play(music);

    // Set booleans to control mouse button
    sfBool activeCar1 = sfTrue;
    sfBool mouseHeld = sfFalse;
    sfBool clickedCar = sfTrue;

    // Start the game loop
    while (sfRenderWindow_isOpen(gameWindowInfo->window))
    {
        // Save a mouse position
        sfVector2i mousePosI = sfMouse_getPosition((const sfWindow *) gameWindowInfo->window);
        sfVector2f mousePosF;
        mousePosF.x = (float) mousePosI.x;
        mousePosF.y = (float) mousePosI.y;

        // Process events
        while (sfRenderWindow_pollEvent(gameWindowInfo->window, &event))
        {
            // Close window : exit
            if (event.type == sfEvtClosed){
                sfRenderWindow_close(gameWindowInfo->window);
                return 0;
            }
            if (event.type == sfEvtMouseButtonPressed){
                if(!mouseHeld){
                    // Capture only one signal
                    mouseHeld = sfTrue;
                    if(!clickedCar){

                        // Check which car was clicked
                        if (mInsideSprite(mousePosF, car1.beginPos, sizeCar) && activeCar1) {
                            clickedCar = sfTrue;
                        } else if (mInsideSprite(mousePosF, car2.beginPos, sizeCar) && !activeCar1) {
                            clickedCar = sfTrue;
                        }
                    }else{

                        // Check which circle was clicked
                        if (mInsideCircle(car1.beginPos, CIRCLE_R, mousePosF) && activeCar1 && clickedCar){
                            clickedCar = sfFalse;
                            activeCar1 = sfFalse;
                            mChangeVector(&car1, mousePosF, onTrack, gameWindowInfo->windowSize);
                        }
                        if (mInsideCircle(car2.beginPos, CIRCLE_R, mousePosF) && !activeCar1 && clickedCar){
                            clickedCar = sfFalse;
                            activeCar1 = sfTrue;
                            mChangeVector(&car2, mousePosF, onTrack, gameWindowInfo->windowSize);
                        }
                    }
                }
            } else{
                mouseHeld = sfFalse;
                break;
            }
        }

        // Count rotation and vectors
        mRotate(&car1);
        mRotate(&car2);

        // Update position
        mPosition(&car1);
        mPosition(&car2);

        // Clear the screen
        sfRenderWindow_clear(gameWindowInfo->window, sfBlack);

        // Draw background, cars, vectors
        sfRenderWindow_drawSprite(gameWindowInfo->window, gameWindowInfo->backgroundSprite, NULL);
        mDraw(&car1, gameWindowInfo->window);
        mDraw(&car2, gameWindowInfo->window);

        // Draw circle when car was clicked
        if(clickedCar){
            if(activeCar1)
                sfRenderWindow_drawCircleShape(gameWindowInfo->window, car1.circle, NULL);
            else
                sfRenderWindow_drawCircleShape(gameWindowInfo->window, car2.circle, NULL);
        }

        // Update the window
        sfRenderWindow_display(gameWindowInfo->window);
    }

    // Cleanup resources
    sfMusic_destroy(music);
    sfSprite_destroy(gameWindowInfo->backgroundSprite);
    sfRenderWindow_destroy(gameWindowInfo->window);
    free(gameWindowInfo);
    free(onTrack);
    return 0;
}