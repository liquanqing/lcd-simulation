#include "hostplatformsurface.h"

#include <QImage>
#include <QPainter>

HostPlatformSurface::HostPlatformSurface(QImage::Format format, QObject *parent) : QObject(parent)
, m_width(0)
, m_format(format)
{

}

HostPlatformSurface &HostPlatformSurface::instance()
{
    static HostPlatformSurface in(QImage::Format_RGB16);
    return in;
}

void HostPlatformSurface::surfaceUpdated(const unsigned char *fb, int x, int y, int width, int height)
{
    int bpp = bitsPerPixel();
    if (bpp && !m_image.isNull()) {
        QPainter painter(&m_image);
        QRect target(x, y, width, height);
        QRect source(0, 0, width, height);
        QImage image(fb, width, height, m_width * bpp, m_format);
        painter.drawImage(target, image, source);
        emit updateSignal(m_image, QRect(x, y, width, height));
    }
}

void HostPlatformSurface::surfaceSizeChanged(int width, int height)
{
    int bpp = bitsPerPixel();
    if (bpp) {
        m_image = QImage(width, height, m_format);
        m_width = width;
        emit resizeSignal(m_image);
    }
}

int HostPlatformSurface::bitsPerPixel()
{
    int ret = 0;
    switch (m_format) {
    case QImage::Format_RGB16:
        ret = 2;
        break;
    case QImage::Format_RGB888:
        ret = 4;
        break;
    default:
        break;
    }
    return ret;
}

