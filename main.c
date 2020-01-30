#include "headers.h"


int main()
{
    int trackID = 0;
    sfBool winnerPlayer1 = sfTrue;
    welcomeWindow(&trackID);
    if(trackID == 0)
        return 0;
    if(gameWindow(trackID, &winnerPlayer1) == 2)
        return 0;
    goodbyeWindow(winnerPlayer1);
    return 0;
}