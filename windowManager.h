#include "headers.h"

struct managerWindowInfo{
    sfRenderWindow* window;
    sfSprite* backgroundSprite;
};

typedef struct managerWindowInfo *mWindowInfo;

mWindowInfo mInitInfo(sfRenderWindow* window, sfSprite* sprite);
sfBool insideSprite(sfVector2f pos, sfVector2f center, sfVector2f size);
sfSprite* mCreateSprite(char *fileName, sfBool setCenter);
mWindowInfo mCreateWindow (const wchar_t titlePL[], sfVector2u windowSize, sfBool center, char backgroundName[] );