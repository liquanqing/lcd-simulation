#include "surfacewidget.h"

#include <QPainter>
#include <QPaintEvent>

SurfaceWidget::SurfaceWidget(QWidget *parent) : QWidget(parent)
, m_image(NULL)
{

}

void SurfaceWidget::updateSlot(QImage *image, const QRect &rect)
{
    m_image = image;
    update(rect);
}

void SurfaceWidget::resizeSlot(int width, int height)
{
    setFixedSize(QSize(width, height));
}

void SurfaceWidget::paintEvent(QPaintEvent *event)
{
    if (m_image) {
        QPainter painter(this);
        painter.drawImage(event->rect(), *m_image);
    }
}

