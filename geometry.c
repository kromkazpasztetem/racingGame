#include "headers.h"

int mRound(float f){
    int val = (int) f;
    f-= (float) val;
    if(f>0.5)
        val++;
    return val;
}

float fAbs(float a){
    if(a>=0)
        return a;
    return -a;
}

float fSquare(float a){
    return a*a;
}

sfCircleShape *mCircle(float radius, sfColor outlineColor){
    sfCircleShape *circle = sfCircleShape_create();
    sfCircleShape_setRadius(circle, radius);
    sfVector2f origin;
    origin.x = radius;
    origin.y = radius;
    sfCircleShape_setOrigin(circle, origin);
    sfColor empty = sfColor_fromInteger(0);
    sfCircleShape_setFillColor(circle, empty);
    sfCircleShape_setOutlineColor(circle, outlineColor);
    sfCircleShape_setOutlineThickness(circle, 5);
    return circle;
}

void mVectorHead(sfVector2f pos){

}

void mVector(sfRenderWindow* window, sfVector2f posFrom, sfVector2f posTo){

}

sfBool mInsideCircle(sfVector2f origin, float radius, sfVector2f point){
    if( fSquare(fAbs(origin.x-point.x)) + fSquare(fAbs(origin.y-point.y)) <= fSquare(radius) )
        return sfTrue;
    return sfFalse;
}