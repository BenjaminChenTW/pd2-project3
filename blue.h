#ifndef BLUE_H
#define BLUE_H

#include "color.h"

class blue : public color
{
public:
    blue(QPushButton *temp);
    virtual void setType();
    virtual void showColor();
    ~blue();
};

#endif // BLUE_H
