#include "headers.h"

struct managerWindowInfo{
    sfRenderWindow* window;
    sfSprite* backgroundSprite;
    sfTexture* backgroundTexture;
};

typedef struct managerWindowInfo *mWindowInfo;

mWindowInfo mInitInfo(sfRenderWindow* window, sfTexture* texture, sfSprite* sprite);
mWindowInfo mCreateWindow (const wchar_t titlePL[], sfVector2u windowSize, sfBool center, uint backgroundID);
