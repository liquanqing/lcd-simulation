#include "mainwidget.h"
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QVBoxLayout>

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    plcd = new lcd;

    upBtn = new QPushButton(tr("UP"));
    dnBtn = new QPushButton(tr("DOWN"));
    leftBtn = new QPushButton(tr("LEFT"));
    rightBtn = new QPushButton(tr("RIGHT"));
    enBtn = new QPushButton(tr("Enter"));
    cnBtn = new QPushButton(tr("Cancel"));
#if MAIN_WIDGET_BTN_FIX_SIZE
    upBtn->setFixedSize(100,50);
    dnBtn->setFixedSize(100,50);
    leftBtn->setFixedSize(100,50);
    rightBtn->setFixedSize(100,50);
    enBtn->setFixedSize(100,50);
    cnBtn->setFixedSize(100,50);
#endif
    rightLayout = new QGridLayout;
    rightLayout->addWidget(upBtn, 0, 0);
    rightLayout->addWidget(dnBtn, 1, 0);
    rightLayout->addWidget(leftBtn, 2, 0);
    rightLayout->addWidget(rightBtn, 3, 0);
    rightLayout->addWidget(enBtn, 4, 0);
    rightLayout->addWidget(cnBtn, 5, 0);

    QVBoxLayout *btnLayout = new QVBoxLayout();
    QSpacerItem *verticalSpacer = new QSpacerItem(10, 10,
                                                 QSizePolicy::Minimum,
                                                 QSizePolicy::Expanding);
    btnLayout->addItem(verticalSpacer);
    btnLayout->addLayout(rightLayout);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(plcd);
    mainLayout->addLayout(btnLayout);
    plcd->clear();
    plcd->draw_rect(0, 0, 128, 64, 1);
    //plcd->draw_rect(1, 1, 126, 62, 1);
    plcd->draw_rect(2, 2, 124, 60, 1);
    //plcd->draw_rect(3, 3, 122, 58, 1);
    plcd->draw_rect(4, 4, 120, 56, 1);
    //plcd->draw_rect(5, 5, 118, 54, 1);
    plcd->draw_rect(6, 6, 116, 52, 1);
    //plcd->draw_rect(7, 7, 114, 50, 1);
    plcd->draw_rect(8, 8, 112, 48, 1);
    //plcd->draw_rect(9, 9, 110, 46, 1);
    plcd->draw_rect(10, 10, 108, 44, 1);
    //plcd->draw_rect(11, 11, 106, 42, 1);
    plcd->draw_rect(12, 12, 104, 40, 1);
    //plcd->draw_rect(13, 13, 102, 38, 1);
    plcd->draw_rect(14, 14, 100, 36, 1);
    //plcd->draw_rect(15, 15,  98, 34, 1);
    plcd->draw_rect(16, 16,  96, 32, 1);
    //plcd->draw_rect(17, 17,  94, 30, 1);
    plcd->draw_rect(18, 18,  92, 28, 1);
    //plcd->draw_rect(19, 19,  90, 26, 1);
    plcd->draw_rect(20, 20,  88, 24, 1);
    //plcd->draw_rect(21, 21,  86, 22, 1);
    plcd->draw_rect(22, 22,  84, 20, 1);
    //plcd->draw_rect(23, 23,  82, 18, 1);
    plcd->draw_rect(24, 24,  80, 16, 1);
    //plcd->draw_rect(25, 25,  78, 14, 1);
    plcd->draw_rect(26, 26,  76, 12, 1);
   // plcd->draw_rect(27, 27,  74, 10, 1);
    plcd->draw_rect(28, 28,  72, 8, 1);
    //plcd->draw_rect(29, 29,  70, 6, 1);
    plcd->draw_rect(30, 30,  68, 4, 1);
    //plcd->draw_rect(31, 31,  66, 2, 1);
}
