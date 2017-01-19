#include "mainwindow.h"

#include "hostplatformsurface.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    HostPlatformSurface *surface = dynamic_cast<HostPlatformSurface *>(HostPlatformSurface::instance());
    connect(this, SIGNAL(drawRectSignal()), &m_worker, SLOT(drawRectSlot()));
    connect(surface, SIGNAL(updateSignal(QImage,QRect)), &m_painter, SLOT(updateSlot(QImage,QRect)));
    connect(surface, SIGNAL(resizeSignal(int,int)), &m_painter, SLOT(resizeSlot(int,int)));
    setCentralWidget(&m_painter);
    m_worker.initialize();
    emit drawRectSignal();
}

MainWindow::~MainWindow()
{
    m_worker.finalize();
}
