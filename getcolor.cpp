#include "getcolor.h"

color *getColor(color *temp, QPushButton *button)
{
    int randNum;
    randNum = qrand() % 5;
    switch (randNum) {
    case Red:
        temp = new red(button);
        break;
    case Yellow:
        temp = new yellow(button);
        break;
    case Green:
        temp = new green(button);
        break;
    case Blue:
        temp = new blue(button);
        break;
    case Purple:
        temp = new purple(button);
        break;
    default:
        break;
    }
    return temp;
}
