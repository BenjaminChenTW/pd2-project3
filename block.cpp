#include "block.h"

block::block()
{
    empty = true;
}

void block::setButton(QPushButton *temp)
{
    button = temp;
}

QPushButton *block::getButton()
{
    return button;
}

void block::setEmpty(bool &temp)
{
    empty = temp;
}

bool block::getEmpty()
{
    return empty;
}

block::~block()
{

}

