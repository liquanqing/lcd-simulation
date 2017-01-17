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
    void updateSignal(const QRect &rect);
    void resizeSignal(QImage *image);

public slots:

private:
    explicit HostPlatformSurface(QImage::Format format, QObject *parent = 0);
    ~HostPlatformSurface();
    QImage *m_image;
    unsigned char *m_buffer;
    int m_width;
    QImage::Format m_format;
};

#endif // HOSTPLATFORMSURFACE_H
