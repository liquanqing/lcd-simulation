#include "mainwindow.h"

#include "hostplatformsurface.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    HostPlatformSurface *surface = dynamic_cast<HostPlatformSurface *>(HostPlatformSurface::instance());
    connect(&m_painter, SIGNAL(pointerEventSignal(int,int,int)), &m_worker, SLOT(pointerEventSlot(int,int,int)));
    connect(&m_painter, SIGNAL(clearSignal(bool)), &m_worker, SLOT(clearEventSlot(bool)));
    connect(surface, SIGNAL(updateSignal(QImage,QRect)), &m_painter, SLOT(updateSlot(QImage,QRect)));
    connect(surface, SIGNAL(resizeSignal(int,int)), &m_painter, SLOT(resizeSlot(int,int)));
    setCentralWidget(&m_painter);
    m_worker.initialize();
}

MainWindow::~MainWindow()
{
    m_worker.finalize();
}
