#include "mainwindow.h"

#include <QLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
, m_surface(QImage::Format_RGB16)
, m_painter(&m_surface)
, m_worker(&m_surface)
{
    connect(this, SIGNAL(drawRectSignal()), &m_worker, SLOT(drawRectSlot()));
    m_worker.initialize();
    setCentralWidget(&m_painter);
    emit drawRectSignal();
}

MainWindow::~MainWindow()
{
    m_worker.finalize();
}
