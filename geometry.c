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

/*void fSwap(float* a, float* b){
    float c = *a;
    *a = *b;
    *b = c;
}*/

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
            deg=90;
        else
            deg=270;
    } else{
        deg= atan2f(fromPos.y - toPos.y, fromPos.x - toPos.x);

        // Convert radians to degrees
        deg = deg *180/M_PI;
    }
    sfRectangleShape_rotate(line, deg);
    sfRectangleShape_setFillColor(line, color);

    return line;
}


// Check if point is inside the sprite

sfBool mInsideSprite(sfVector2f pos, sfVector2f center, sfVector2f size){
    if(pos.x > center.x - size.x/2 && pos.x < center.x + size.x/2
       && pos.y > center.y - size.y/2 && pos.y < center.y + size.y/2)
        return sfTrue;
    return sfFalse;
}

// Check if point is inside the circle

sfBool mInsideCircle(sfVector2f origin, float radius, sfVector2f point){

    // |x1-x2|^2 + |y1-y2|^2 <= r^2, circle definition
    if( fSquare(fAbs(origin.x-point.x)) + fSquare(fAbs(origin.y-point.y)) <= fSquare(radius) )
        return sfTrue;
    return sfFalse;
}

// Check if two line segments have common point

sfBool mCrossLines(sfVector2f m1, sfVector2f m2, sfVector2f n1, sfVector2f n2){
    sfVector2f deltaM, deltaN;
    deltaM.y = m2.y - m1.y;
    deltaM.x = m2.x - m1.x;
    if( (deltaM.x == 0 && deltaM.y == 0) || (deltaN.x == 0 && deltaN.y == 0) )
        return sfFalse;

    deltaN.y = n2.y - n1.y;
    deltaN.x = n2.x - n1.x;

    sfVector2f point;
    float aM, aN, bM, bN;

    if(deltaM.x == 0){
        if(deltaN.x == 0)
            return sfFalse;
        point.x = m1.x;
    } else{
        aM = deltaM.y / deltaM.x;
        bM = m1.y - aM * m1.x;
    }
    if(deltaN.x == 0){
        point.x = n1.x;
    }else{
        aN = deltaN.y / deltaN.x;
        bN = n1.y - aN * n1.x;
    }

    if(deltaM.x == 0){
        point.y = aN * point.x + bN;
    } else if(deltaN.x == 0){
        point.y = aM * point.x + bM;
    } else{
        if (aM == aN)
            return sfFalse;
        point.x = (bN - bM) / (aM - aN);
        point.y = aM * point.x + bM;
    }

    if( fAbs(point.x-m1.x) <= fAbs(deltaM.x) && fAbs(point.x - m2.x) <= fAbs(deltaM.x) &&
        fAbs(point.x-n1.x) <= fAbs(deltaN.x) && fAbs(point.x - n2.x) <= fAbs(deltaN.x) &&
        fAbs(point.y-m1.y) <= fAbs(deltaM.y) && fAbs(point.y - m2.y) <= fAbs(deltaM.y) &&
        fAbs(point.y-n1.y) <= fAbs(deltaN.y) && fAbs(point.y - n2.y) <= fAbs(deltaN.y)   )
        return sfTrue;
    return sfFalse;
}