#ifndef HOSTPLATFORMSURFACE_H
#define HOSTPLATFORMSURFACE_H

#include <QObject>
#include <QRect>
#include <QImage>

#include "platformsurface.h"

class HostPlatformSurface : public QObject, public PlatformSurface
{
    Q_OBJECT
public:
    static HostPlatformSurface &instance();
    void surfaceUpdated(const unsigned char *fb, int x, int y, int width, int height);
    void surfaceSizeChanged(int width, int height);
    int bitsPerPixel();

signals:
    void updateSignal(QImage image, const QRect &rect);
    void resizeSignal(int width, int height);

public slots:

private:
    explicit HostPlatformSurface(QImage::Format format, QObject *parent = 0);
    QImage m_image;
    int m_width;
    QImage::Format m_format;
};

#endif // HOSTPLATFORMSURFACE_H
