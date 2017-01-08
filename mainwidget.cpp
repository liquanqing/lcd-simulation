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
    for (int i = 0; i < 128; i++) {
        plcd->draw_pix(i, 0, 1);
        plcd->draw_pix(i, 63, 1);
    }
    for (int i = 0; i < 64; i++) {
        plcd->draw_pix(0, i, 1);
        plcd->draw_pix(127, i, 1);
    }

    for (int i = 0; i < 11; i ++) {
        plcd->draw_pix(i+30, 5, 1);
    }

    for (int i = 0; i < 11; i ++) {
        plcd->draw_pix(35, i + 2, 1);
    }

}
