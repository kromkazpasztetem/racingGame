#include "headers.h"

struct car{
    sfSprite* image;
    sfVector2f beginPos;
    sfVector2f endPos;
    sfRectangleShape* vectorLine;
    sfCircleShape* vectorSpike;
    sfCircleShape* circle;
    sfColor vectorColor;
};

typedef struct car* ptrCar;

struct car initCar(int carID, sfColor color);
sfBool** readTrack();
void mChangeVector(ptrCar carPtr, sfVector2f mousePos, sfBool** onTrack, sfVector2u windowSize);
void mRotate(ptrCar carPtr);
void mPosition(ptrCar carPtr);
void mDraw(ptrCar carPtr, sfRenderWindow* gameWindow);
int gameWindow(int trackID);