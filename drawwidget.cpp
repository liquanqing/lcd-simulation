#include "drawwidget.h"
#include <QtGui>
#include <QPen>
#include <QPainter>

DrawWidget::DrawWidget(QWidget *parent) : QWidget(parent)
{
    setAutoFillBackground(true);
    setPalette(QPalette(Qt::white));
    pix = new QPixmap(size());
    pix->fill(Qt::white);
    //setMinimumSize(600, 400);
    setFixedSize(200, 200);
}


void DrawWidget::setStyle(int s)
{
    style = s;
}

void DrawWidget::setColor(QColor c)
{
    color = c;
}

void DrawWidget::setWidth(int w)
{
    weight = w;
}

void DrawWidget::mousePressEvent(QMouseEvent *e)
{
    startPos = e->pos();
}

void DrawWidget::mouseMoveEvent(QMouseEvent *e)
{
    QPainter *painter = new QPainter;
    QPen pen;
    pen.setStyle((Qt::PenStyle)style);
    pen.setWidth(weight);
    pen.setColor(color);
    painter->begin(pix);
    painter->setPen(pen);
    painter->drawLine(startPos, e->pos());
    painter->end();
    startPos = e->pos();
    update();
}

void DrawWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    painter.drawPixmap(QPoint(0, 0), *pix);
}

void DrawWidget::resizeEvent(QResizeEvent *e)
{
    if (height()>pix->height() || width() > pix->width()) {
        QPixmap *newPix = new QPixmap(size());
        newPix->fill(Qt::white);
        QPainter p(newPix);
        p.drawPixmap(QPoint(0, 0), *pix);
        pix = newPix;
    }
    QWidget::resizeEvent(e);
}

void DrawWidget::clear()
{
    QPixmap *clearPix = new QPixmap(size());
    clearPix->fill(Qt::white);
    pix = clearPix;
    update();
}
