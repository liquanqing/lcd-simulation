#ifndef SURFACEWIDGET_H
#define SURFACEWIDGET_H

#include <QWidget>

class HostPlatformSurface;
class QImage;

class SurfaceWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SurfaceWidget(HostPlatformSurface *surface, QWidget *parent = 0);

signals:

public slots:
    void updateSlot(QImage *image, const QRect &rect);
    void resizeSlot(int width, int height);

private:
    void paintEvent(QPaintEvent *event);
    QImage *m_image;
};

#endif // SURFACEWIDGET_H
