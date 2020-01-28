#include "headers.h"

int fRound(float f){
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

    // Create a circle around of the car
    sfCircleShape *circle = sfCircleShape_create();
    sfCircleShape_setRadius(circle, radius);
    sfVector2f origin;
    origin.x = radius;
    origin.y = radius;
    sfCircleShape_setOrigin(circle, origin);
    sfColor empty = sfColor_fromInteger(0);
    sfCircleShape_setFillColor(circle, empty);
    sfCircleShape_setOutlineColor(circle, outlineColor);
    sfCircleShape_setOutlineThickness(circle, 2);
    return circle;
}

sfCircleShape * mVectorSpike(float radius, sfColor fillColor){

    // Create spike of the vector
    sfCircleShape* triangle = sfCircleShape_create();
    sfCircleShape_setPointCount(triangle, 3);
    sfCircleShape_setRadius(triangle, radius);
    sfVector2f origin;
    origin.x = radius;
    origin.y = radius;
    sfCircleShape_setOrigin(triangle, origin);
    sfCircleShape_setFillColor(triangle, fillColor);
    return triangle;
}

sfRectangleShape* mVectorLine(sfVector2f fromPos, sfVector2f toPos, sfColor color){

    // Create line of the vector
    sfRectangleShape* line = sfRectangleShape_create();
    sfVector2f size;

    // a^2 + b^2 = c^2, length of vector (Pythagorean theorem)
    size.x = sqrtf(fSquare(fAbs(fromPos.x - toPos.x)) + fSquare(fAbs(fromPos.y - toPos.y)) );
    if(size.x == 0)
        return NULL;
    size.y = 2;
    sfRectangleShape_setSize(line, size);

    // Set origin in the first point
    size.y /=2;
    sfRectangleShape_setOrigin(line, size);
    sfRectangleShape_setPosition(line, fromPos);

    // Rotate line (arctan(y/x)=angle in radians)
    float deg;
    if(fromPos.x == toPos.x){
        if(fromPos.x > toPos.x)
            deg=270;
        else
            deg=90;
    } else{
        deg= atan2f(fromPos.y - toPos.y, fromPos.x - toPos.x);

        // Convert radians to degrees
        deg = deg *180/M_PI;
    }
    sfRectangleShape_rotate(line, deg);
    sfRectangleShape_setFillColor(line, color);

    return line;
}

sfBool mInsideCircle(sfVector2f origin, float radius, sfVector2f point){

    // |x1-x2|^2 + |y1-y2|^2 <= r^2, circle definition
    if( fSquare(fAbs(origin.x-point.x)) + fSquare(fAbs(origin.y-point.y)) <= fSquare(radius) )
        return sfTrue;
    return sfFalse;
}