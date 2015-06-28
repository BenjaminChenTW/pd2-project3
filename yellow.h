#ifndef YELLOW_H
#define YELLOW_H

#include "color.h"

class yellow : public color
{
public:
    yellow(QPushButton *temp);
    virtual void setType();
    virtual void showColor();
    ~yellow();
};

#endif // YELLOW_H
