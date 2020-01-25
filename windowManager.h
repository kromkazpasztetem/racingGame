#include "headers.h"

int mRound(float f);

struct managerWindowInfo{
    sfRenderWindow* window;
    sfSprite* backgroundSprite;
    sfVector2u windowSize;
};

typedef struct managerWindowInfo *mWindowInfo;

mWindowInfo mInitInfo(sfRenderWindow* window, sfSprite* sprite, sfVector2u windowSize);
sfBool insideSprite(sfVector2f pos, sfVector2f center, sfVector2f size);
sfSprite* mCreateSprite(char *fileName, sfBool setCenter);
mWindowInfo mCreateWindow (const sfUint32 *titlePL, sfVector2u windowSize, sfBool center, char backgroundName []);