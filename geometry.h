#include "headers.h"

int fRound(float f);
float fAbs(float a);
float fSquare(float a);
sfCircleShape *mCircle(float radius, sfColor outlineColor);
sfCircleShape * mVectorSpike(float radius, sfColor fillColor);
sfRectangleShape* mVectorLine(sfVector2f fromPos, sfVector2f toPos, sfColor color);
sfBool mInsideSprite(sfVector2f pos, sfVector2f center, sfVector2f size);
sfBool mInsideCircle(sfVector2f origin, float radius, sfVector2f point);