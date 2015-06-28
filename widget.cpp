#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <time.h>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    qsrand(time(NULL));
    connectBlocks();
    checkedCtr = 0;
    //while (checkMap(1)) {}
    //qDebug() << (*colors[0][0]==*colors[1][1]);
}

Widget::~Widget()
{
    emit quit(stars,score);
    delete ui;
}

void Widget::changeColor(color **color1, color **color2)
{
    color *colorsTemp[2];
    switch ((*color1)->getType()) {
    case Red:
        colorsTemp[1] = new red((*color2)->getButton());
        break;
    case Yellow:
        colorsTemp[1] = new yellow((*color2)->getButton());
        break;
    case Green:
        colorsTemp[1] = new green((*color2)->getButton());
        break;
    case Blue:
        colorsTemp[1] = new blue((*color2)->getButton());
        break;
    case Purple:
        colorsTemp[1] = new purple((*color2)->getButton());
        break;
    default:
        break;
    }
    switch ((*color2)->getType()) {
    case Red:
        colorsTemp[0] = new red((*color1)->getButton());
        break;
    case Yellow:
        colorsTemp[0] = new yellow((*color1)->getButton());
        break;
    case Green:
        colorsTemp[0] = new green((*color1)->getButton());
        break;
    case Blue:
        colorsTemp[0] = new blue((*color1)->getButton());
        break;
    case Purple:
        colorsTemp[0] = new purple((*color1)->getButton());
        break;
    default:
        break;
    }
    colorsTemp[0]->getButton()->setChecked(false);
    colorsTemp[1]->getButton()->setChecked(false);
    colorsTemp[0]->setXY((*color1)->getX(), (*color1)->getY());
    colorsTemp[1]->setXY((*color2)->getX(), (*color2)->getY());
    delete *color1;
    delete *color2;
    *color1 = colorsTemp[0];
    *color2 = colorsTemp[1];
    (*color1)->showColor();
    (*color2)->showColor();
    checkedCtr = 0;
}

void Widget::deleteColor(color *temp)
{
    color *deleteTemp;
    deleteTemp = temp;
    blocks[temp->getX()][temp->getY()].setEmpty(true);
    colors[temp->getX()][temp->getY()] = NULL;
    delete deleteTemp;
}

bool Widget::checkMap(int mode)
{

}

void Widget::fillMap()
{

}

void Widget::check(color **temp1, color ** temp2)
{
    int x0 = (*temp1)->getX();
    int y0 = (*temp1)->getY();
    int x1 = (*temp2)->getX();
    int y1 = (*temp2)->getY();
    if (!((x0==x1&&(y0-y1)==1) || (x0==x1&&(y0-y1)==-1) || (y0==y1&&(x0-x1)==1) || (y0==y1&&(x0-x1)==-1))){
        (*temp1)->getButton()->setChecked(false);
        (*temp2)->getButton()->setChecked(false);
        checkedCtr = 0;
        return;
    }
    changeColor(temp1, temp2);
    rule(temp1);
    if (!(rule(temp2))){changeColor(temp1, temp2);}
}

void Widget::toggledEvent(bool checked, int x, int y)
{
    if (colors[x][y]->getType() == Horizontal){
        for (int i=0; i<9; i++){
            deleteColor(colors[x][i]);
        }
    }
    else if (colors[x][y]->getType() == Vertical){
        for (int i=0; i<9; i++){
            deleteColor(colors[i][y]);
        }
    }
    else if (colors[x][y]->getType() == Bomb){
        for (int i=x-1; i<x+2; i++){
            for (int j=y-1; j<y+2; j++){
                deleteColor(colors[i][j]);
            }
        }
    }
    else if (colors[x][y]->getType() == Star){

    }
    else {
        checked ? checkedCtr++ : checkedCtr--;
        if (checkedCtr == 1){
            colorTemp1 = &colors[x][y];
        }
        else if (checkedCtr ==2){
            colorTemp2 = &colors[x][y];
            check(colorTemp1, colorTemp2);
        }
        else if (checkedCtr == 0) {}
        else {
            qDebug() << "checkedCtr ERROR!!! :" << checkedCtr;
            checkedCtr = 0;
        }
    }
}

bool Widget::rule(color **temp)
{
    int xCtr = 1, yCtr = 1;
    const int xTemp = (*temp)->getX();
    const int yTemp = (*temp)->getY();
    color *colorX[4];
    color *colorY[4];
    for(int i=0; i<4; i++){
        colorX[i] = NULL;
        colorY[i] = NULL;
    }
    for(int x=xTemp+1 , i=2; x <= xTemp+2; x++, i++){
        if (x > 9) break;
        if(**temp==*colors[x][yTemp]){
            xCtr++;
            colorX[i]=colors[x][yTemp];
        }
        else break;
    }
    for(int x=xTemp-1, i=1; x >= xTemp-2; x--, i--){
        if (x < 0) break;
        if(**temp==*colors[x][yTemp]){
            xCtr++;
            colorY[i]=colors[x][yTemp];
        }
        else break;
    }
    for(int y=yTemp+1, i=2; y <= yTemp+2; y++, i++){
        if (y > 9) break;
        if(**temp==*colors[xTemp][y]){
            yCtr++;
            colorY[i]=colors[xTemp][y];
        }
        else break;
    }
    for(int y=yTemp-1, i=1; y >= yTemp-2; y--, i--){
        if (y < 0) break;
        if (**temp==*colors[xTemp][y]){
            yCtr++;
            colorY[i]=colors[xTemp][y];
        }
        else break;
    }

    if (xCtr > 3 && yCtr >3){
        color *newTemp[1];
        for (int i=0; i<4; i++){
            if(colorX[i] != NULL){
                deleteColor(colorX[i]);
            }
            if(colorY[i] != NULL){
                deleteColor(colorY[i]);
            }
        }
        newTemp[0] = new bomb((*temp)->getButton());
        (newTemp[0])->setXY((*temp)->getX(),(*temp)->getY());
        delete *temp;
        *temp = newTemp[0];
        (*temp)->showColor();
        return true;
    }
    else if (xCtr >=5 || yCtr >=5){
        color *newTemp[1];
        for (int i=0; i<4; i++){
            if(colorX[i] != NULL){
                deleteColor(colorX[i]);
            }
            if(colorY[i] != NULL){
                deleteColor(colorY[i]);
            }
        }
        newTemp[0] = new star((*temp)->getButton());
        (newTemp[0])->setXY((*temp)->getX(),(*temp)->getY());
        delete *temp;
        *temp = newTemp[0];
        (*temp)->showColor();
        return true;
    }
    else if (xCtr >=4){
        color *newTemp[1];
        for (int i=0; i<4; i++){
            if(colorX[i] != NULL){
                deleteColor(colorX[i]);
            }
            if(colorY[i] != NULL){
                deleteColor(colorY[i]);
            }
        }
        newTemp[0] = new vertical((*temp)->getButton());
        (newTemp[0])->setXY((*temp)->getX(),(*temp)->getY());
        delete *temp;
        *temp = newTemp[0];
        (*temp)->showColor();
        return true;
    }
    else if (yCtr >=4){
        color *newTemp[1];
        for (int i=0; i<4; i++){
            if(colorX[i] != NULL){
                deleteColor(colorX[i]);
            }
            if(colorY[i] != NULL){
                deleteColor(colorY[i]);
            }
        }
        newTemp[0] = new horizontal((*temp)->getButton());
        (newTemp[0])->setXY((*temp)->getX(),(*temp)->getY());
        delete *temp;
        *temp = newTemp[0];
        (*temp)->showColor();
        return true;
    }
    else if (xCtr >=3 || yCtr >=3){
        for (int i=0; i<4; i++){
            if(colorX[i] != NULL){
                deleteColor(colorX[i]);
            }
            if(colorY[i] != NULL){
                deleteColor(colorY[i]);
            }
        }
        deleteColor(*temp);
        return true;
    }
    else {return false;}
}

void Widget::connectBlocks()
{
    blocks[0][0].setButton(ui->pushButton);
    blocks[0][1].setButton(ui->pushButton_2);
    blocks[0][2].setButton(ui->pushButton_3);
    blocks[0][3].setButton(ui->pushButton_4);
    blocks[0][4].setButton(ui->pushButton_5);
    blocks[0][5].setButton(ui->pushButton_6);
    blocks[0][6].setButton(ui->pushButton_7);
    blocks[0][7].setButton(ui->pushButton_8);
    blocks[0][8].setButton(ui->pushButton_9);
    blocks[0][9].setButton(ui->pushButton_10);
    blocks[1][0].setButton(ui->pushButton_11);
    blocks[1][1].setButton(ui->pushButton_12);
    blocks[1][2].setButton(ui->pushButton_13);
    blocks[1][3].setButton(ui->pushButton_14);
    blocks[1][4].setButton(ui->pushButton_15);
    blocks[1][5].setButton(ui->pushButton_16);
    blocks[1][6].setButton(ui->pushButton_17);
    blocks[1][7].setButton(ui->pushButton_18);
    blocks[1][8].setButton(ui->pushButton_19);
    blocks[1][9].setButton(ui->pushButton_20);
    blocks[2][0].setButton(ui->pushButton_21);
    blocks[2][1].setButton(ui->pushButton_22);
    blocks[2][2].setButton(ui->pushButton_23);
    blocks[2][3].setButton(ui->pushButton_24);
    blocks[2][4].setButton(ui->pushButton_25);
    blocks[2][5].setButton(ui->pushButton_26);
    blocks[2][6].setButton(ui->pushButton_27);
    blocks[2][7].setButton(ui->pushButton_28);
    blocks[2][8].setButton(ui->pushButton_29);
    blocks[2][9].setButton(ui->pushButton_30);
    blocks[3][0].setButton(ui->pushButton_31);
    blocks[3][1].setButton(ui->pushButton_32);
    blocks[3][2].setButton(ui->pushButton_33);
    blocks[3][3].setButton(ui->pushButton_34);
    blocks[3][4].setButton(ui->pushButton_35);
    blocks[3][5].setButton(ui->pushButton_36);
    blocks[3][6].setButton(ui->pushButton_37);
    blocks[3][7].setButton(ui->pushButton_38);
    blocks[3][8].setButton(ui->pushButton_39);
    blocks[3][9].setButton(ui->pushButton_40);
    blocks[4][0].setButton(ui->pushButton_41);
    blocks[4][1].setButton(ui->pushButton_42);
    blocks[4][2].setButton(ui->pushButton_43);
    blocks[4][3].setButton(ui->pushButton_44);
    blocks[4][4].setButton(ui->pushButton_45);
    blocks[4][5].setButton(ui->pushButton_46);
    blocks[4][6].setButton(ui->pushButton_47);
    blocks[4][7].setButton(ui->pushButton_48);
    blocks[4][8].setButton(ui->pushButton_49);
    blocks[4][9].setButton(ui->pushButton_50);
    blocks[5][0].setButton(ui->pushButton_51);
    blocks[5][1].setButton(ui->pushButton_52);
    blocks[5][2].setButton(ui->pushButton_53);
    blocks[5][3].setButton(ui->pushButton_54);
    blocks[5][4].setButton(ui->pushButton_55);
    blocks[5][5].setButton(ui->pushButton_56);
    blocks[5][6].setButton(ui->pushButton_57);
    blocks[5][7].setButton(ui->pushButton_58);
    blocks[5][8].setButton(ui->pushButton_59);
    blocks[5][9].setButton(ui->pushButton_60);
    blocks[6][0].setButton(ui->pushButton_61);
    blocks[6][1].setButton(ui->pushButton_62);
    blocks[6][2].setButton(ui->pushButton_63);
    blocks[6][3].setButton(ui->pushButton_64);
    blocks[6][4].setButton(ui->pushButton_65);
    blocks[6][5].setButton(ui->pushButton_66);
    blocks[6][6].setButton(ui->pushButton_67);
    blocks[6][7].setButton(ui->pushButton_68);
    blocks[6][8].setButton(ui->pushButton_69);
    blocks[6][9].setButton(ui->pushButton_70);
    blocks[7][0].setButton(ui->pushButton_71);
    blocks[7][1].setButton(ui->pushButton_72);
    blocks[7][2].setButton(ui->pushButton_73);
    blocks[7][3].setButton(ui->pushButton_74);
    blocks[7][4].setButton(ui->pushButton_75);
    blocks[7][5].setButton(ui->pushButton_76);
    blocks[7][6].setButton(ui->pushButton_77);
    blocks[7][7].setButton(ui->pushButton_78);
    blocks[7][8].setButton(ui->pushButton_79);
    blocks[7][9].setButton(ui->pushButton_80);
    blocks[8][0].setButton(ui->pushButton_81);
    blocks[8][1].setButton(ui->pushButton_82);
    blocks[8][2].setButton(ui->pushButton_83);
    blocks[8][3].setButton(ui->pushButton_84);
    blocks[8][4].setButton(ui->pushButton_85);
    blocks[8][5].setButton(ui->pushButton_86);
    blocks[8][6].setButton(ui->pushButton_87);
    blocks[8][7].setButton(ui->pushButton_88);
    blocks[8][8].setButton(ui->pushButton_89);
    blocks[8][9].setButton(ui->pushButton_90);
    blocks[9][0].setButton(ui->pushButton_91);
    blocks[9][1].setButton(ui->pushButton_92);
    blocks[9][2].setButton(ui->pushButton_93);
    blocks[9][3].setButton(ui->pushButton_94);
    blocks[9][4].setButton(ui->pushButton_95);
    blocks[9][5].setButton(ui->pushButton_96);
    blocks[9][6].setButton(ui->pushButton_97);
    blocks[9][7].setButton(ui->pushButton_98);
    blocks[9][8].setButton(ui->pushButton_99);
    blocks[9][9].setButton(ui->pushButton_100);
}

void Widget::on_pushButton_toggled(bool checked){toggledEvent(checked,0,0);}
void Widget::on_pushButton_2_toggled(bool checked){toggledEvent(checked,0,1);}
void Widget::on_pushButton_3_toggled(bool checked){toggledEvent(checked,0,2);}
void Widget::on_pushButton_4_toggled(bool checked){toggledEvent(checked,0,3);}
void Widget::on_pushButton_5_toggled(bool checked){toggledEvent(checked,0,4);}
void Widget::on_pushButton_6_toggled(bool checked){toggledEvent(checked,0,5);}
void Widget::on_pushButton_7_toggled(bool checked){toggledEvent(checked,0,6);}
void Widget::on_pushButton_8_toggled(bool checked){toggledEvent(checked,0,7);}
void Widget::on_pushButton_9_toggled(bool checked){toggledEvent(checked,0,8);}
void Widget::on_pushButton_10_toggled(bool checked){toggledEvent(checked,0,9);}
void Widget::on_pushButton_11_toggled(bool checked){toggledEvent(checked,1,0);}
void Widget::on_pushButton_12_toggled(bool checked){toggledEvent(checked,1,1);}
void Widget::on_pushButton_13_toggled(bool checked){toggledEvent(checked,1,2);}
void Widget::on_pushButton_14_toggled(bool checked){toggledEvent(checked,1,3);}
void Widget::on_pushButton_15_toggled(bool checked){toggledEvent(checked,1,4);}
void Widget::on_pushButton_16_toggled(bool checked){toggledEvent(checked,1,5);}
void Widget::on_pushButton_17_toggled(bool checked){toggledEvent(checked,1,6);}
void Widget::on_pushButton_18_toggled(bool checked){toggledEvent(checked,1,7);}
void Widget::on_pushButton_19_toggled(bool checked){toggledEvent(checked,1,8);}
void Widget::on_pushButton_20_toggled(bool checked){toggledEvent(checked,1,9);}
void Widget::on_pushButton_21_toggled(bool checked){toggledEvent(checked,2,0);}
void Widget::on_pushButton_22_toggled(bool checked){toggledEvent(checked,2,1);}
void Widget::on_pushButton_23_toggled(bool checked){toggledEvent(checked,2,2);}
void Widget::on_pushButton_24_toggled(bool checked){toggledEvent(checked,2,3);}
void Widget::on_pushButton_25_toggled(bool checked){toggledEvent(checked,2,4);}
void Widget::on_pushButton_26_toggled(bool checked){toggledEvent(checked,2,5);}
void Widget::on_pushButton_27_toggled(bool checked){toggledEvent(checked,2,6);}
void Widget::on_pushButton_28_toggled(bool checked){toggledEvent(checked,2,7);}
void Widget::on_pushButton_29_toggled(bool checked){toggledEvent(checked,2,8);}
void Widget::on_pushButton_30_toggled(bool checked){toggledEvent(checked,2,9);}
void Widget::on_pushButton_31_toggled(bool checked){toggledEvent(checked,3,0);}
void Widget::on_pushButton_32_toggled(bool checked){toggledEvent(checked,3,1);}
void Widget::on_pushButton_33_toggled(bool checked){toggledEvent(checked,3,2);}
void Widget::on_pushButton_34_toggled(bool checked){toggledEvent(checked,3,3);}
void Widget::on_pushButton_35_toggled(bool checked){toggledEvent(checked,3,4);}
void Widget::on_pushButton_36_toggled(bool checked){toggledEvent(checked,3,5);}
void Widget::on_pushButton_37_toggled(bool checked){toggledEvent(checked,3,6);}
void Widget::on_pushButton_38_toggled(bool checked){toggledEvent(checked,3,7);}
void Widget::on_pushButton_39_toggled(bool checked){toggledEvent(checked,3,8);}
void Widget::on_pushButton_40_toggled(bool checked){toggledEvent(checked,3,9);}
void Widget::on_pushButton_41_toggled(bool checked){toggledEvent(checked,4,0);}
void Widget::on_pushButton_42_toggled(bool checked){toggledEvent(checked,4,1);}
void Widget::on_pushButton_43_toggled(bool checked){toggledEvent(checked,4,2);}
void Widget::on_pushButton_44_toggled(bool checked){toggledEvent(checked,4,3);}
void Widget::on_pushButton_45_toggled(bool checked){toggledEvent(checked,4,4);}
void Widget::on_pushButton_46_toggled(bool checked){toggledEvent(checked,4,5);}
void Widget::on_pushButton_47_toggled(bool checked){toggledEvent(checked,4,6);}
void Widget::on_pushButton_48_toggled(bool checked){toggledEvent(checked,4,7);}
void Widget::on_pushButton_49_toggled(bool checked){toggledEvent(checked,4,8);}
void Widget::on_pushButton_50_toggled(bool checked){toggledEvent(checked,4,9);}
void Widget::on_pushButton_51_toggled(bool checked){toggledEvent(checked,5,0);}
void Widget::on_pushButton_52_toggled(bool checked){toggledEvent(checked,5,1);}
void Widget::on_pushButton_53_toggled(bool checked){toggledEvent(checked,5,2);}
void Widget::on_pushButton_54_toggled(bool checked){toggledEvent(checked,5,3);}
void Widget::on_pushButton_55_toggled(bool checked){toggledEvent(checked,5,4);}
void Widget::on_pushButton_56_toggled(bool checked){toggledEvent(checked,5,5);}
void Widget::on_pushButton_57_toggled(bool checked){toggledEvent(checked,5,6);}
void Widget::on_pushButton_58_toggled(bool checked){toggledEvent(checked,5,7);}
void Widget::on_pushButton_59_toggled(bool checked){toggledEvent(checked,5,8);}
void Widget::on_pushButton_60_toggled(bool checked){toggledEvent(checked,5,9);}
void Widget::on_pushButton_61_toggled(bool checked){toggledEvent(checked,6,0);}
void Widget::on_pushButton_62_toggled(bool checked){toggledEvent(checked,6,1);}
void Widget::on_pushButton_63_toggled(bool checked){toggledEvent(checked,6,2);}
void Widget::on_pushButton_64_toggled(bool checked){toggledEvent(checked,6,3);}
void Widget::on_pushButton_65_toggled(bool checked){toggledEvent(checked,6,4);}
void Widget::on_pushButton_66_toggled(bool checked){toggledEvent(checked,6,5);}
void Widget::on_pushButton_67_toggled(bool checked){toggledEvent(checked,6,6);}
void Widget::on_pushButton_68_toggled(bool checked){toggledEvent(checked,6,7);}
void Widget::on_pushButton_69_toggled(bool checked){toggledEvent(checked,6,8);}
void Widget::on_pushButton_70_toggled(bool checked){toggledEvent(checked,6,9);}
void Widget::on_pushButton_71_toggled(bool checked){toggledEvent(checked,7,0);}
void Widget::on_pushButton_72_toggled(bool checked){toggledEvent(checked,7,1);}
void Widget::on_pushButton_73_toggled(bool checked){toggledEvent(checked,7,2);}
void Widget::on_pushButton_74_toggled(bool checked){toggledEvent(checked,7,3);}
void Widget::on_pushButton_75_toggled(bool checked){toggledEvent(checked,7,4);}
void Widget::on_pushButton_76_toggled(bool checked){toggledEvent(checked,7,5);}
void Widget::on_pushButton_77_toggled(bool checked){toggledEvent(checked,7,6);}
void Widget::on_pushButton_78_toggled(bool checked){toggledEvent(checked,7,7);}
void Widget::on_pushButton_79_toggled(bool checked){toggledEvent(checked,7,8);}
void Widget::on_pushButton_80_toggled(bool checked){toggledEvent(checked,7,9);}
void Widget::on_pushButton_81_toggled(bool checked){toggledEvent(checked,8,0);}
void Widget::on_pushButton_82_toggled(bool checked){toggledEvent(checked,8,1);}
void Widget::on_pushButton_83_toggled(bool checked){toggledEvent(checked,8,2);}
void Widget::on_pushButton_84_toggled(bool checked){toggledEvent(checked,8,3);}
void Widget::on_pushButton_85_toggled(bool checked){toggledEvent(checked,8,4);}
void Widget::on_pushButton_86_toggled(bool checked){toggledEvent(checked,8,5);}
void Widget::on_pushButton_87_toggled(bool checked){toggledEvent(checked,8,6);}
void Widget::on_pushButton_88_toggled(bool checked){toggledEvent(checked,8,7);}
void Widget::on_pushButton_89_toggled(bool checked){toggledEvent(checked,8,8);}
void Widget::on_pushButton_90_toggled(bool checked){toggledEvent(checked,8,9);}
void Widget::on_pushButton_91_toggled(bool checked){toggledEvent(checked,9,0);}
void Widget::on_pushButton_92_toggled(bool checked){toggledEvent(checked,9,1);}
void Widget::on_pushButton_93_toggled(bool checked){toggledEvent(checked,9,2);}
void Widget::on_pushButton_94_toggled(bool checked){toggledEvent(checked,9,3);}
void Widget::on_pushButton_95_toggled(bool checked){toggledEvent(checked,9,4);}
void Widget::on_pushButton_96_toggled(bool checked){toggledEvent(checked,9,5);}
void Widget::on_pushButton_97_toggled(bool checked){toggledEvent(checked,9,6);}
void Widget::on_pushButton_98_toggled(bool checked){toggledEvent(checked,9,7);}
void Widget::on_pushButton_99_toggled(bool checked){toggledEvent(checked,9,8);}
void Widget::on_pushButton_100_toggled(bool checked){toggledEvent(checked,9,9);}

void Widget::on_pushButton_101_clicked()
{
    ui->pushButton_101->setEnabled(false);
    ui->pushButton_101->setVisible(false);
    for (int i=0; i<10; i++){
        for (int j=0; j<10; j++){
            colors[j][i] = getColor(blocks[j][i].getButton());
            colors[j][i]->setXY(j, i);
            blocks[j][i].setEmpty(false);
        }
    }
}
