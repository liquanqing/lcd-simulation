#include "mainwindow.h"

#include <QLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
, m_painter(NULL)
{
    m_painter = new(std::nothrow) SurfaceWidget(&m_surface);
    connect(this, SIGNAL(drawRectSignal()), &m_worker, SLOT(drawRectSlot()));
    m_worker.initialize(&m_surface);
    setCentralWidget(m_painter);
    emit drawRectSignal();
}

MainWindow::~MainWindow()
{
    m_worker.finalize();
    delete m_painter;
}
