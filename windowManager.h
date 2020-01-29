#include "headers.h"

int fRound(float f);

struct managerWindowInfo{
    sfRenderWindow* window;
    sfSprite* backgroundSprite;
    sfVector2u windowSize;
};

typedef struct managerWindowInfo *mWindowInfo;

mWindowInfo mInitInfo(sfRenderWindow* window, sfSprite* sprite, sfVector2u windowSize);
sfSprite* mCreateSprite(char *fileName, sfBool setCenter);
mWindowInfo mCreateWindow (const sfUint32 *titlePL, sfVector2u windowSize, sfBool center, int backgroundID);