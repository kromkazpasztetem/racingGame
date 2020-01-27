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
void mRotate(ptrCar carPtr);
int gameWindow();