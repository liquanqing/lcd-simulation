#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "surfacewidget.h"
#include "workthread.h"
#include "hostplatformsurface.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void drawRectSignal();

private:
    SurfaceWidget *m_painter;
    HostPlatformSurface m_surface;
    WorkThread m_worker;
};

#endif // MAINWINDOW_H
