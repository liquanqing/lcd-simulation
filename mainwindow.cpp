#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    Qt::WindowFlags flags = 0;
    flags |= Qt::WindowFullscreenButtonHint;
    flags |= Qt::MSWindowsFixedSizeDialogHint;
     MainWidget *mainWidget = new MainWidget;
    setWindowFlags(flags);
    setCentralWidget(mainWidget);

}

MainWindow::~MainWindow()
{

}
