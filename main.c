#include "headers.h"


int main()
{
    int trackID = 0;
    welcomeWindow(&trackID);
    if(trackID == 0)
        return 0;
    gameWindow(trackID);
    return 0;
}