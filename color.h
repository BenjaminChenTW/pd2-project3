#ifndef COLOR_H
#define COLOR_H

#include <QPushButton>

enum colorType{
    Red = 0, Yellow = 1, Green = 2, Blue = 3, Purple = 4
};

class color
{
public:
    color(QPushButton *temp);
    void setButton(QPushButton *temp);
    virtual void setType()=0;
    colorType &getType();
    virtual void showColor()=0;
    ~color();
protected:
    QPushButton* button;
    colorType type;
};

#endif // COLOR_H
