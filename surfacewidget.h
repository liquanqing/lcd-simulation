#ifndef SURFACEWIDGET_H
#define SURFACEWIDGET_H

#include <QWidget>

class QImage;

class SurfaceWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SurfaceWidget(QWidget *parent = 0);

signals:

public slots:
    void updateSlot(const QRect &rect);
    void resizeSlot(QImage *image);

private:
    void paintEvent(QPaintEvent *event);
    QImage *m_image;
};

#endif // SURFACEWIDGET_H
