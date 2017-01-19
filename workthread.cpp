#include "workthread.h"

#include "hostplatformsurface.h"
#include "bitmapbasiclcd.h"
#include "utils.h"

#define LCD_WIDTH 128
#define LCD_HEIGHT 64

WorkThread::WorkThread(QObject *parent) : QObject(parent)
, m_controller(NULL)
{
}

WorkThread::~WorkThread()
{
    delete m_controller;
}

void WorkThread::initialize()
{
    HostPlatformSurface *surface = dynamic_cast<HostPlatformSurface *>(HostPlatformSurface::instance());
    surface->setColorFormat(QImage::Format_RGB16);
    m_controller = new(std::nothrow) BitmapBasicLCD(surface, LCD_WIDTH, LCD_HEIGHT, bitsPerPixel(QImage::Format_RGB16));
    moveToThread(&m_thread);
    m_thread.start();
}

void WorkThread::finalize()
{
    m_thread.quit();
    m_thread.wait();
    delete m_controller;
    m_controller = NULL;
}

void WorkThread::drawRectSlot()
{
    m_controller->clear();
    m_controller->draw_rect(0, 0, 128, 64, 0xFF);
    m_controller->draw_circle(50, 30, 30, 0xFF);
    m_controller->draw_round_rect(3, 3, 20, 10, 3, 0xFF);
}

