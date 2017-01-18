#include "surfacewidget.h"

#include <QPainter>
#include <QPaintEvent>

#define WIDGET_WIDTH  800
#define WIDGET_HEIGHT 480

SurfaceWidget::SurfaceWidget(QWidget *parent) : QWidget(parent)
{
    setFixedSize(QSize(WIDGET_WIDTH, WIDGET_HEIGHT));
}

void SurfaceWidget::updateSlot(QImage image, const QRect &rect)
{
    m_image = image;
    m_image.setDevicePixelRatio(m_ratio);
    update(rect);
}

void SurfaceWidget::resizeSlot(QImage image)
{
    if (image.height() < image.width()) {
        m_ratio = image.width() / (qreal)WIDGET_WIDTH;
    }
    else {
        m_ratio = image.height() / (qreal)WIDGET_HEIGHT;
    }
    if (WIDGET_HEIGHT * image.width() > WIDGET_WIDTH * image.height()) {
        m_point.setX(0);
        m_point.setY(WIDGET_HEIGHT / 2 - image.height() / m_ratio / 2);
    }
    else if (WIDGET_HEIGHT * image.width() != WIDGET_WIDTH * image.height()) {
        m_point.setX(WIDGET_WIDTH / 2 - image.width() / m_ratio / 2);
        m_point.setY(0);
    }
    else {
        m_point.setX(0);
        m_point.setY(0);
    }
}

void SurfaceWidget::paintEvent(QPaintEvent *event)
{
    if (!m_image.isNull()) {
        QPainter painter(this);
        painter.drawImage(m_point, m_image, event->rect());
    }
}

