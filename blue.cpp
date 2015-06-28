#include "blue.h"

blue::blue(QPushButton *temp) : color(temp)
{
    setType();
    showColor();
}

void blue::setType()
{
    type = Blue;
}

void blue::showColor()
{
    button->setStyleSheet("{background-color: #84C1FF;}");
    button->setAutoFillBackground(true);
}

blue::~blue()
{

}

