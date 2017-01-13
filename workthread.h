#ifndef WORKTHREAD_H
#define WORKTHREAD_H

#include <QObject>
#include <QThread>

#include "bitmapbasiclcd.h"

class PlatformSurface;

class WorkThread : public QObject
{
    Q_OBJECT
public:
    explicit WorkThread(QObject *parent = 0);
    void initialize();
    void finalize();

signals:

public slots:
    void drawRectSlot();

private:
    QThread m_thread;
    BitmapBasicLCD m_controller;
};

#endif // WORKTHREAD_H
