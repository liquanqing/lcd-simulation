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
    void pointerEventSignal(int x, int y, int b);

public slots:
    void updateSlot(QImage image, const QRect &rect);
    void resizeSlot(int width, int height);

private:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    QImage m_image;
    QPointF m_point;
    qreal m_ratio;
};

#endif // SURFACEWIDGET_H
