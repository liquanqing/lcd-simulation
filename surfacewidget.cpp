#include "surfacewidget.h"

#include "hostplatformsurface.h"

#include <QPainter>
#include <QPaintEvent>

SurfaceWidget::SurfaceWidget(HostPlatformSurface *surface, QWidget *parent) : QWidget(parent)
, m_image(NULL)
{
    connect(surface, SIGNAL(updateSignal(QImage*,QRect)), this, SLOT(updateSlot(QImage*,QRect)));
    connect(surface, SIGNAL(resizeSignal(int,int)), this, SLOT(resizeSlot(int,int)));
    show();
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

