#include "green.h"

green::green(QPushButton *temp) : color(temp)
{
    setType();
    showColor();
}

void green::setType()
{
    type = Green;
}

void green::showColor()
{
    button->setStyleSheet("QPushButton {background-color: #CCFF80;}");
}

green::~green()
{

}

