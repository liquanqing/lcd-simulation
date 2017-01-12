#ifndef HOSTPLATFORMSURFACE_H
#define HOSTPLATFORMSURFACE_H

#include <QObject>
#include <QRect>

#include "platformsurface.h"

class QImage;

class HostPlatformSurface : public QObject, public PlatformSurface
{
    Q_OBJECT
public:
    explicit HostPlatformSurface(QObject *parent = 0);
    ~HostPlatformSurface();
    void surfaceUpdated(const unsigned char *fb, int x, int y, int width, int height);
    void surfaceSizeChanged(int width, int height);

signals:
    void updateSignal(QImage *image, const QRect &rect);
    void resizeSignal(int width, int height);

public slots:

private:
    QImage *m_image;
    unsigned char *m_buffer;
    int m_width;
};

#endif // HOSTPLATFORMSURFACE_H
