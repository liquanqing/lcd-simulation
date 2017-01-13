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
    delete m_image;
    m_image = new(std::nothrow) QImage(*image);
    m_image->setDevicePixelRatio(ratio);
}

void SurfaceWidget::paintEvent(QPaintEvent *event)
{
    if (m_image) {
        QPainter painter(this);
        painter.drawImage(event->rect(), *m_image);
    }
}

