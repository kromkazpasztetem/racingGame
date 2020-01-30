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

sfBool** readTrack(int trackID){

    // Allocate space
    sfBool **binaryMap;
    if (( binaryMap =(sfBool**) malloc( MAPSIZE_X * sizeof( sfBool* ))) == NULL )
        return NULL;
    for(int x=0; x<MAPSIZE_X; x++) {
        if ((binaryMap[x] = (sfBool *) malloc(MAPSIZE_Y * sizeof(sfBool))) == NULL)
            return NULL;
    }

    // Read a racing track from file as a 0-1 table
    char fileName [50];
    sprintf(fileName,"./tracks/track%d.txt", trackID);
    FILE* binaryFile = fopen( fileName, "r");
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

void mSetStartPos(ptrCar carPtr1, ptrCar carPtr2, sfVector2f* finish1, sfVector2f* finish2, int trackID){
    switch (trackID){
        case 1:
            carPtr1->beginPos.x = 834;
            carPtr1->beginPos.y = 94;
            carPtr2->beginPos.x = 834;
            carPtr2->beginPos.y = 52;
            finish1->x = 836;
            finish1->y = 20;
            finish2->x = 836;
            finish2->y = 120;
            break;
        case 2:
            carPtr1->beginPos.x = 450;
            carPtr1->beginPos.y = 490;
            carPtr2->beginPos.x = 450;
            carPtr2->beginPos.y = 530;
            finish1->x = 440;
            finish1->y = 450;
            finish2->x = 450;
            finish2->y = 560;
            break;
        case 3:
            carPtr1->beginPos.x = 894;
            carPtr1->beginPos.y = 758;
            carPtr2->beginPos.x = 894;
            carPtr2->beginPos.y = 800;
            finish1->x = carPtr1->beginPos.x+2;
            finish1->y = 724;
            finish2->x = finish1->x;
            finish2->y = 828;
            break;
    }
    carPtr1->endPos = carPtr1->beginPos;
    carPtr2->endPos = carPtr2->beginPos;
}

int gameWindow(int trackID, sfBool* winnerPlayer1){

    int closed = 0;

    // Create window, set title, size, background, declare resources
    sfVector2u windowSize;
    windowSize.x = 0;
    mWindowInfo window2Info = mCreateWindow(L"Wyścigi samochodowe - trwa wyścig", windowSize, sfTrue, trackID);
    if (window2Info->window == NULL)
        return 1;
    //sfFont* font;
    sfMusic* music;
    sfEvent event;
    sfBool** onTrack = readTrack(trackID);

    struct car car1 = initCar(1, sfBlue);
    struct car car2 = initCar(2, sfYellow);

    // Create cars
    sfFloatRect sizeCarTemp = sfSprite_getLocalBounds(car1.image);
    sfVector2f sizeCar;
    sizeCar.x = sizeCarTemp.width;
    sizeCar.y = sizeCarTemp.height;

    // Set default position for each track
    sfVector2f finish1, finish2;
    mSetStartPos(&car1, &car2, &finish1, &finish2, trackID);

    // Load a music to play
    music = sfMusic_createFromFile("./music/gameMusic.wav");
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
    while (sfRenderWindow_isOpen(window2Info->window))
    {
        // Save a mouse position
        sfVector2i mousePosI = sfMouse_getPosition((const sfWindow *) window2Info->window);
        sfVector2f mousePosF;
        mousePosF.x = (float) mousePosI.x;
        mousePosF.y = (float) mousePosI.y;

        // Process events
        while (sfRenderWindow_pollEvent(window2Info->window, &event))
        {
            // Close window : exit
            if (event.type == sfEvtClosed){
                sfRenderWindow_close(window2Info->window);
                closed +=2;
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
                        sfVector2f startPos1, startPos2;
                        startPos1 = car1.beginPos;
                        startPos2 = car2.beginPos;

                        // Check which circle was clicked
                        if (mInsideCircle(car1.beginPos, CIRCLE_R, mousePosF) && activeCar1 && clickedCar){
                            clickedCar = sfFalse;
                            activeCar1 = sfFalse;
                            mChangeVector(&car1, mousePosF, onTrack, window2Info->windowSize);
                        }
                        if (mInsideCircle(car2.beginPos, CIRCLE_R, mousePosF) && !activeCar1 && clickedCar){
                            clickedCar = sfFalse;
                            activeCar1 = sfTrue;
                            mChangeVector(&car2, mousePosF, onTrack, window2Info->windowSize);
                        }

                        if(startPos1.x != car1.beginPos.x) {
                            if (mCrossLines(startPos1, car1.beginPos, finish1, finish2))
                                sfRenderWindow_close(window2Info->window);
                        } else if (startPos2.x != car2.beginPos.x){
                            if (mCrossLines(startPos2, car2.beginPos, finish1, finish2)){
                                sfRenderWindow_close(window2Info->window);
                                *winnerPlayer1 = sfFalse;
                            }
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

        if(car1.vectorLine == NULL && trackID == 2)
            sfSprite_setRotation(car1.image, 177);
        if(car2.vectorLine == NULL && trackID == 2)
            sfSprite_setRotation(car2.image, 177);

        // Update position
        mPosition(&car1);
        mPosition(&car2);

        // Clear the screen
        sfRenderWindow_clear(window2Info->window, sfBlack);

        // Draw background, cars, vectors
        sfRenderWindow_drawSprite(window2Info->window, window2Info->backgroundSprite, NULL);
        mDraw(&car1, window2Info->window);
        mDraw(&car2, window2Info->window);

        // Draw circle when car was clicked
        if(clickedCar){
            if(activeCar1)
                sfRenderWindow_drawCircleShape(window2Info->window, car1.circle, NULL);
            else
                sfRenderWindow_drawCircleShape(window2Info->window, car2.circle, NULL);
        }

        // Update the window
        sfRenderWindow_display(window2Info->window);
    }

    // Cleanup resources
    sfMusic_destroy(music);
    sfSprite_destroy(window2Info->backgroundSprite);
    sfRenderWindow_destroy(window2Info->window);
    free(window2Info);
    free(onTrack);
    return 0 + closed;
}