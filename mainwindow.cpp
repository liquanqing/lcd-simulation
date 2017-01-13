#include "mainwindow.h"

#include "hostplatformsurface.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    connect(this, SIGNAL(drawRectSignal()), &m_worker, SLOT(drawRectSlot()));
    connect(&HostPlatformSurface::instance(), SIGNAL(updateSignal(QImage*,QRect)), &m_painter, SLOT(updateSlot(QImage*,QRect)));
    connect(&HostPlatformSurface::instance(), SIGNAL(resizeSignal(int,int)), &m_painter, SLOT(resizeSlot(int,int)));
    setCentralWidget(&m_painter);
    m_worker.initialize();
    emit drawRectSignal();
}

MainWindow::~MainWindow()
{
    m_worker.finalize();
}
