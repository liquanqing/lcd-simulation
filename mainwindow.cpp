#include "mainwindow.h"

#include <QLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
, m_surface(QImage::Format_RGB16)
, m_worker(&m_surface)
{
    connect(this, SIGNAL(drawRectSignal()), &m_worker, SLOT(drawRectSlot()));
    connect(&m_surface, SIGNAL(updateSignal(QImage*,QRect)), &m_painter, SLOT(updateSlot(QImage*,QRect)));
    connect(&m_surface, SIGNAL(resizeSignal(int,int)), &m_painter, SLOT(resizeSlot(int,int)));
    m_worker.initialize();
    setCentralWidget(&m_painter);
    emit drawRectSignal();
}

MainWindow::~MainWindow()
{
    m_worker.finalize();
}
