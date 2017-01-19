#include "hostplatformsurface.h"

#include "utils.h"

#include <QImage>
#include <QPainter>

HostPlatformSurface::HostPlatformSurface(QObject *parent) : QObject(parent)
, m_width(0)
{
}

PlatformSurface *HostPlatformSurface::instance()
{
    static HostPlatformSurface in;
    return &in;
}

void HostPlatformSurface::setColorFormat(QImage::Format format)
{
    m_format = format;
}

void HostPlatformSurface::surfaceUpdated(const unsigned char *fb, int x, int y, int width, int height)
{
    int bpp = bitsPerPixel(m_format);
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
    int bpp = bitsPerPixel(m_format);
    if (bpp) {
        m_image = QImage(width, height, m_format);
        m_width = width;
        emit resizeSignal(width, height);
    }
}

