#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include <QGridLayout>
#include <QSpacerItem>
#include "lcd.h"

#define MAIN_WIDGET_BTN_FIX_SIZE    0

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();
signals:

public slots:

private:
    lcd *plcd;
    QPushButton *upBtn;
    QPushButton *dnBtn;
    QPushButton *leftBtn;
    QPushButton *rightBtn;
    QPushButton *enBtn;
    QPushButton *cnBtn;
    QGridLayout *rightLayout;
};

#endif // MAINWIDGET_H
