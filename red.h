#ifndef RED_H
#define RED_H

#include "color.h"

class red : public color
{
public:
    red(QPushButton *temp);
    virtual void setType();
    virtual void showColor();
    ~red();
};

#endif // RED_H
