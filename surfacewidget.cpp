#include "surfacewidget.h"

#include <QPainter>
#include <QPaintEvent>

#define WIDGET_WIDTH  800
#define WIDGET_HEIGHT 480

SurfaceWidget::SurfaceWidget(QWidget *parent) : QWidget(parent)
, m_image(NULL)
{
    setFixedSize(QSize(WIDGET_WIDTH, WIDGET_HEIGHT));
}

void SurfaceWidget::updateSlot(const QRect &rect)
{
    update(rect);
}

void SurfaceWidget::resizeSlot(QImage *image)
{
    qreal ratio = 0;
    if (image->height() < image->width()) {
        ratio = image->width() / (qreal)WIDGET_WIDTH;
    }
    else {
        ratio = image->height() / (qreal)WIDGET_HEIGHT;
    }
    if (WIDGET_HEIGHT * image->width() > WIDGET_WIDTH * image->height()) {
        m_point.setX(0);
        m_point.setY(WIDGET_HEIGHT / 2 - image->height() / ratio / 2);
    }
    else if (WIDGET_HEIGHT * image->width() != WIDGET_WIDTH * image->height()) {
        m_point.setX(WIDGET_WIDTH / 2 - image->width() / ratio / 2);
        m_point.setY(0);
    }
    else {
        m_point.setX(0);
        m_point.setY(0);
    }
    delete m_image;
    m_image = new(std::nothrow) QImage(*image);
    m_image->setDevicePixelRatio(ratio);
}

void SurfaceWidget::paintEvent(QPaintEvent *event)
{
    if (m_image) {
        QPainter painter(this);
        painter.drawImage(m_point, *m_image, event->rect());
    }
}

