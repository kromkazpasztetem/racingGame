#include "headers.h"

int fRound(float f);
float fAbs(float a);
float fSquare(float a);
sfCircleShape *mCircle(float radius, sfColor outlineColor);
sfCircleShape * mVectorTriangle(float radius, sfColor fillColor);
sfRectangleShape* mVectorLine(sfVector2f fromPos, sfVector2f toPos, sfColor color);
sfBool mInsideCircle(sfVector2f origin, float radius, sfVector2f point);
