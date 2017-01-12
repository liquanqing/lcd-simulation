#include "hostplatformsurface.h"

#include <QImage>
#include <QPainter>

HostPlatformSurface::HostPlatformSurface(QObject *parent) : QObject(parent)
, m_image(NULL)
, m_buffer(NULL)
, m_width(0)
{

}

HostPlatformSurface::~HostPlatformSurface()
{
    delete m_image;
    delete [] m_buffer;
}

void HostPlatformSurface::surfaceUpdated(const unsigned char *fb, int x, int y, int width, int height)
{
    if (m_image) {
        QPainter painter(m_image);
        QRect target(x, y, width, height);
        QRect source(0, 0, width, height);
        QImage image(fb, width, height, m_width * 2, QImage::Format_RGB16);
        painter.drawImage(target, image, source);
        emit updateSignal(m_image, QRect(x, y, width, height));
    }
}

void HostPlatformSurface::surfaceSizeChanged(int width, int height)
{
    delete m_image;
    delete [] m_buffer;
    m_buffer = new(std::nothrow) unsigned char[width * height * 2];
    m_image = new(std::nothrow) QImage(m_buffer, width, height, width * 2, QImage::Format_RGB16);
    m_width = width;
    emit resizeSignal(width, height);
}

