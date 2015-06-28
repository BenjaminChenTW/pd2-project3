#ifndef PURPLE_H
#define PURPLE_H

#include "color.h"

class purple : public color
{
public:
    purple(QPushButton *temp);
    virtual void setType();
    virtual void showColor();
    ~purple();
};

#endif // PURPLE_H
