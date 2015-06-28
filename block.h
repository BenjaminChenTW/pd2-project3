#ifndef BLOCK_H
#define BLOCK_H

#include<QPushButton>

class block
{
public:
    block();
    void setButton(QPushButton *temp);
    QPushButton* getButton();
    void setEmpty(bool &temp);
    bool getEmpty();
    ~block();
private:
    QPushButton* button;
    bool empty;
};

#endif // BLOCK_H
