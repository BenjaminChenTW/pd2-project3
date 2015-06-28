#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "block.h"
#include "color.h"
#include "getcolor.h"
#include "red.h"
#include "yellow.h"
#include "blue.h"
#include "green.h"
#include "purple.h"
#include "horizontal.h"
#include "vertical.h"
#include "bomb.h"
#include "star.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

signals:
    void quit(int star, int score);

private slots:
    void on_pushButton_toggled(bool checked);
    void on_pushButton_2_toggled(bool checked);
    void on_pushButton_3_toggled(bool checked);
    void on_pushButton_4_toggled(bool checked);
    void on_pushButton_5_toggled(bool checked);
    void on_pushButton_6_toggled(bool checked);
    void on_pushButton_7_toggled(bool checked);
    void on_pushButton_8_toggled(bool checked);
    void on_pushButton_9_toggled(bool checked);
    void on_pushButton_10_toggled(bool checked);
    void on_pushButton_11_toggled(bool checked);
    void on_pushButton_12_toggled(bool checked);
    void on_pushButton_13_toggled(bool checked);
    void on_pushButton_14_toggled(bool checked);
    void on_pushButton_15_toggled(bool checked);
    void on_pushButton_16_toggled(bool checked);
    void on_pushButton_17_toggled(bool checked);
    void on_pushButton_18_toggled(bool checked);
    void on_pushButton_19_toggled(bool checked);
    void on_pushButton_20_toggled(bool checked);
    void on_pushButton_21_toggled(bool checked);
    void on_pushButton_22_toggled(bool checked);
    void on_pushButton_23_toggled(bool checked);
    void on_pushButton_24_toggled(bool checked);
    void on_pushButton_25_toggled(bool checked);
    void on_pushButton_26_toggled(bool checked);
    void on_pushButton_27_toggled(bool checked);
    void on_pushButton_28_toggled(bool checked);
    void on_pushButton_29_toggled(bool checked);
    void on_pushButton_30_toggled(bool checked);
    void on_pushButton_31_toggled(bool checked);
    void on_pushButton_32_toggled(bool checked);
    void on_pushButton_33_toggled(bool checked);
    void on_pushButton_34_toggled(bool checked);
    void on_pushButton_35_toggled(bool checked);
    void on_pushButton_36_toggled(bool checked);
    void on_pushButton_37_toggled(bool checked);
    void on_pushButton_38_toggled(bool checked);
    void on_pushButton_39_toggled(bool checked);
    void on_pushButton_40_toggled(bool checked);
    void on_pushButton_41_toggled(bool checked);
    void on_pushButton_42_toggled(bool checked);
    void on_pushButton_43_toggled(bool checked);
    void on_pushButton_44_toggled(bool checked);
    void on_pushButton_45_toggled(bool checked);
    void on_pushButton_46_toggled(bool checked);
    void on_pushButton_47_toggled(bool checked);
    void on_pushButton_48_toggled(bool checked);
    void on_pushButton_49_toggled(bool checked);
    void on_pushButton_50_toggled(bool checked);
    void on_pushButton_51_toggled(bool checked);
    void on_pushButton_52_toggled(bool checked);
    void on_pushButton_53_toggled(bool checked);
    void on_pushButton_54_toggled(bool checked);
    void on_pushButton_55_toggled(bool checked);
    void on_pushButton_56_toggled(bool checked);
    void on_pushButton_57_toggled(bool checked);
    void on_pushButton_58_toggled(bool checked);
    void on_pushButton_59_toggled(bool checked);
    void on_pushButton_60_toggled(bool checked);
    void on_pushButton_61_toggled(bool checked);
    void on_pushButton_62_toggled(bool checked);
    void on_pushButton_63_toggled(bool checked);
    void on_pushButton_64_toggled(bool checked);
    void on_pushButton_65_toggled(bool checked);
    void on_pushButton_66_toggled(bool checked);
    void on_pushButton_67_toggled(bool checked);
    void on_pushButton_68_toggled(bool checked);
    void on_pushButton_69_toggled(bool checked);
    void on_pushButton_70_toggled(bool checked);
    void on_pushButton_71_toggled(bool checked);
    void on_pushButton_72_toggled(bool checked);
    void on_pushButton_73_toggled(bool checked);
    void on_pushButton_74_toggled(bool checked);
    void on_pushButton_75_toggled(bool checked);
    void on_pushButton_76_toggled(bool checked);
    void on_pushButton_77_toggled(bool checked);
    void on_pushButton_78_toggled(bool checked);
    void on_pushButton_79_toggled(bool checked);
    void on_pushButton_80_toggled(bool checked);
    void on_pushButton_81_toggled(bool checked);
    void on_pushButton_82_toggled(bool checked);
    void on_pushButton_83_toggled(bool checked);
    void on_pushButton_84_toggled(bool checked);
    void on_pushButton_85_toggled(bool checked);
    void on_pushButton_86_toggled(bool checked);
    void on_pushButton_87_toggled(bool checked);
    void on_pushButton_88_toggled(bool checked);
    void on_pushButton_89_toggled(bool checked);
    void on_pushButton_90_toggled(bool checked);
    void on_pushButton_91_toggled(bool checked);
    void on_pushButton_92_toggled(bool checked);
    void on_pushButton_93_toggled(bool checked);
    void on_pushButton_94_toggled(bool checked);
    void on_pushButton_95_toggled(bool checked);
    void on_pushButton_96_toggled(bool checked);
    void on_pushButton_97_toggled(bool checked);
    void on_pushButton_98_toggled(bool checked);
    void on_pushButton_99_toggled(bool checked);
    void on_pushButton_100_toggled(bool checked);

    void on_pushButton_101_clicked();

private:
    Ui::Widget *ui;
    int checkedCtr;
    int stars;
    int score;
    void changeColor(color **color1, color **color2);
    void deleteColor(color *temp);
    bool checkMap(int mode);
    void fillMap();
    void check(color **temp1, color **temp2);
    bool rule(color **temp);
    void toggledEvent(bool checked, int x, int y);
    void connectBlocks();
    block blocks[10][10];
    color *colors[10][10];
    color **colorTemp1;
    color **colorTemp2;
};

#endif // WIDGET_H
