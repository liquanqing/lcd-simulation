#include "surfacewidget.h"

#include <QPainter>
#include <QPaintEvent>

SurfaceWidget::SurfaceWidget(QWidget *parent) : QWidget(parent)
, m_image(NULL)
{
    setFixedSize(QSize(800, 480));
}

void SurfaceWidget::updateSlot(const QRect &rect)
{
    update(rect);
}

void SurfaceWidget::resizeSlot(QImage *image)
{
    qreal ratio = 0;
    if (image->height() < image->width()) {
        ratio = image->width() / 800.0;
    }
    else {
        ratio = image->height() / 480.0;
    }
    if (image->height() / ratio < 480) {
        m_point.setX(0);
        m_point.setY(240 - image->height() / ratio / 2);
    }
    else if (image->width() / ratio < 800) {
        m_point.setX(400 - image->width() / ratio / 2);
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

