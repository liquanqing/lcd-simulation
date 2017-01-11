#include "mainwidget.h"
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QVBoxLayout>

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    plcd = new lcd(parent);

    upBtn = new QPushButton(tr("UP"), parent);
    dnBtn = new QPushButton(tr("DOWN"), parent);
    leftBtn = new QPushButton(tr("LEFT"), parent);
    rightBtn = new QPushButton(tr("RIGHT"), parent);
    enBtn = new QPushButton(tr("Enter"), parent);
    cnBtn = new QPushButton(tr("Cancel"), parent);
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
    plcd->draw_rect(10, 10, 50, 50, 1);
    plcd->draw_round_rect(20, 20, 20, 6, 3, 1);
}

MainWidget::~MainWidget()
{
    delete plcd;
    delete upBtn;
    delete dnBtn;
    delete leftBtn;
    delete rightBtn;
    delete enBtn;
    delete cnBtn;
    delete rightLayout;
}

