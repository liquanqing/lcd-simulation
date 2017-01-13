#include "hostplatformsurface.h"

#include <QImage>
#include <QPainter>

HostPlatformSurface::HostPlatformSurface(QImage::Format format, QObject *parent) : QObject(parent)
, m_image(NULL)
, m_buffer(NULL)
, m_width(0)
, m_format(format)
{

}

HostPlatformSurface::~HostPlatformSurface()
{
    delete m_image;
    delete [] m_buffer;
}

void HostPlatformSurface::surfaceUpdated(const unsigned char *fb, int x, int y, int width, int height)
{
    int bpp = bytesPerPixel();
    if (bpp && m_image) {
        QPainter painter(m_image);
        QRect target(x, y, width, height);
        QRect source(0, 0, width, height);
        QImage image(fb, width, height, m_width * bpp, m_format);
        painter.drawImage(target, image, source);
        emit updateSignal(m_image, QRect(x, y, width, height));
    }
}

void HostPlatformSurface::surfaceSizeChanged(int width, int height)
{
    int bpp = bytesPerPixel();
    if (bpp) {
        delete m_image;
        delete [] m_buffer;
        m_buffer = new(std::nothrow) unsigned char[width * height * bpp];
        m_image = new(std::nothrow) QImage(m_buffer, width, height, width * bpp, m_format);
        m_width = width;
        emit resizeSignal(width, height);
    }
}

int HostPlatformSurface::bytesPerPixel()
{
    int ret = 0;
    switch (m_format) {
    case QImage::Format_RGB16:
        ret = 2;
        break;
    case QImage::Format_RGB888:
        ret = 3;
        break;
    default:
        break;
    }
    return ret;
}

