#include "color.h"

color::color(QPushButton *temp)
{
    button = NULL;
    setButton(temp);
    //button->setStyleSheet("QPushButton {border 0px;background-color: #BEBEBE}");
}

void color::setButton(QPushButton *temp)
{
    button = temp;
}

colorType &color::getType()
{
    return type;
}

color::~color()
{
    button->setStyleSheet("QPushButton {background-color: #BEBEBE;}");
}
