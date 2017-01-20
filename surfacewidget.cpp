#include "surfacewidget.h"

#include <QPainter>
#include <QPaintEvent>

#include "utils.h"

#define WIDGET_WIDTH  800
#define WIDGET_HEIGHT 480

SurfaceWidget::SurfaceWidget(QWidget *parent) : QWidget(parent)
, m_ratio(1)
{
    setFixedSize(QSize(WIDGET_WIDTH, WIDGET_HEIGHT));
}

void SurfaceWidget::updateSlot(QImage image, const QRect &rect)
{
    Q_UNUSED(rect);
    m_image = image;
    m_image.setDevicePixelRatio(m_ratio);
    repaint();
}

void SurfaceWidget::resizeSlot(int width, int height)
{
    if (height < width) {
        m_ratio = width / (qreal)WIDGET_WIDTH;
    }
    else {
        m_ratio = height / (qreal)WIDGET_HEIGHT;
    }
    if (WIDGET_HEIGHT * width > WIDGET_WIDTH * height) {
        m_point.setX(0);
        m_point.setY(WIDGET_HEIGHT / 2 - height / m_ratio / 2);
    }
    else if (WIDGET_HEIGHT * width != WIDGET_WIDTH * height) {
        m_point.setX(WIDGET_WIDTH / 2 - width / m_ratio / 2);
        m_point.setY(0);
    }
    else {
        m_point.setX(0);
        m_point.setY(0);
    }
}

int SurfaceWidget::buttonMaskConvert(Qt::MouseButtons button)
{
    switch (button) {
    case Qt::NoButton:
        return BUTTON_MASK_NONE;
    case Qt::LeftButton:
        return BUTTON_MASK_LEFT;
    case Qt::RightButton:
        return BUTTON_MASK_RIGHT;
    case Qt::MidButton:
        return BUTTON_MASK_MID;
    case Qt::BackButton:
        return BUTTON_MASK_BACK;
    case Qt::ForwardButton:
        return BUTTON_MASK_FORWARD;
    default:
        return BUTTON_MASK_NONE;
    }
}

bool SurfaceWidget::isInsideWidget(QPointF p)
{
    if (((p.x() >= m_point.x()) && (p.y() >= m_point.y()))
            && ((p.x() <= m_point.x() + m_image.width() / m_ratio)
                && (p.y() <= m_point.y() + m_image.height() / m_ratio))) {
        return true;
    }
    return false;
}

void SurfaceWidget::paintEvent(QPaintEvent *event)
{
    if (!m_image.isNull()) {
        QPainter painter(this);
        painter.drawImage(m_point, m_image, event->rect());
    }
}

void SurfaceWidget::mouseMoveEvent(QMouseEvent *event)
{
    QPointF p = event->localPos();
    if (isInsideWidget(p)) {
        emit pointerEventSignal(static_cast<int>((p.x() - m_point.x()) * m_ratio),
                                static_cast<int>((p.y() - m_point.y()) * m_ratio),
                                buttonMaskConvert(event->buttons()));
        return;
    }
    QWidget::mouseMoveEvent(event);
}

void SurfaceWidget::mousePressEvent(QMouseEvent *event)
{
    QPointF p = event->localPos();
    if (isInsideWidget(p)) {
        emit pointerEventSignal(static_cast<int>((p.x() - m_point.x()) * m_ratio),
                                static_cast<int>((p.y() - m_point.y()) * m_ratio),
                                buttonMaskConvert(event->button()));
        return;
    }
    QWidget::mousePressEvent(event);
}

void SurfaceWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
}

