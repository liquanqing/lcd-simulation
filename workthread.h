#ifndef WORKTHREAD_H
#define WORKTHREAD_H

#include <QObject>
#include <QThread>

class BitmapBasicLCD;

class WorkThread : public QObject
{
    Q_OBJECT
public:
    explicit WorkThread(QObject *parent = 0);
    ~WorkThread();
    void initialize();
    void finalize();

signals:

public slots:
    void threadStartSlot();
    void pointerEventSlot(int x, int y, int b);
    void clearEventSlot(bool);

private:
    QThread m_thread;
    BitmapBasicLCD *m_controller;
};

#endif // WORKTHREAD_H
