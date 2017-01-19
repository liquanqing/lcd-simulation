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
    static PlatformSurface *instance();
    void setColorFormat(QImage::Format format);
    void surfaceUpdated(const unsigned char *fb, int x, int y, int width, int height);
    void surfaceSizeChanged(int width, int height);

signals:
    void updateSignal(QImage image, const QRect &rect);
    void resizeSignal(int width, int height);

public slots:

private:
    explicit HostPlatformSurface(QObject *parent = 0);
    QImage m_image;
    int m_width;
    QImage::Format m_format;
};

#endif // HOSTPLATFORMSURFACE_H
