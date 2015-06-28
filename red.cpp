#include "red.h"

red::red(QPushButton *temp) : color(temp)
{
    setType();
    showColor();
}

void red::setType()
{
    type = Red;
}

void red::showColor()
{
    button->setStyleSheet("QPushButton {background-color: #FF5151;}");
}

red::~red()
{

}

