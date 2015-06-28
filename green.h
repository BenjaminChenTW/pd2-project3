#ifndef GREEN_H
#define GREEN_H

#include "color.h"

class green : public color
{
public:
    green(QPushButton *temp);
    virtual void setType();
    virtual void showColor();
    ~green();
};

#endif // GREEN_H
