#include "purple.h"

purple::purple(QPushButton *temp) : color(temp)
{
    setType();
    showColor();
}

void purple::setType()
{
    type = Purple;
}

void purple::showColor()
{
    button->setStyleSheet("QPushButton {background-color: #C07AB8;}");
}

purple::~purple()
{

}

