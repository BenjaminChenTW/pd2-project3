#include "yellow.h"

yellow::yellow(QPushButton *temp) : color(temp)
{
    setType();
    showColor();
}

void yellow::setType()
{
    type = Yellow;
}

void yellow::showColor()
{
    button->setStyleSheet("QPushButton {background-color: #FFFF93;}");
}

yellow::~yellow()
{

}

