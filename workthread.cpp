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
    HostPlatformSurface::instance()->setColorFormat(COLOR_FORMAT_RGB888);
    m_controller = new(std::nothrow) BitmapBasicLCD(HostPlatformSurface::instance(),
                                                    LCD_WIDTH,
                                                    LCD_HEIGHT,
                                                    bitsPerPixel(COLOR_FORMAT_RGB888));
    connect(&m_thread, SIGNAL(started()), this, SLOT(threadStartSlot()));
    moveToThread(&m_thread);
    m_thread.start();
}

void WorkThread::finalize()
{
    m_thread.quit();
    m_thread.wait();
    disconnect(&m_thread, SIGNAL(started()), this, SLOT(threadStartSlot()));
    delete m_controller;
    m_controller = NULL;
}

void WorkThread::threadStartSlot()
{
    m_controller->clear();
    m_controller->draw_rect(0, 0, 128, 64, RGB888(0,0,255));
    m_controller->draw_circle(50, 32, 30, RGB888(255,0,0));
    m_controller->draw_round_rect(3, 3, 20, 10, 5, RGB888(255,255,255));
    m_controller->draw_round_rect(30, 3, 20, 10, 5, RGB888(255,255,255));
    m_controller->update();
}

void WorkThread::pointerEventSlot(int x, int y, int b)
{
    if (b == BUTTON_MASK_LEFT) {
        m_controller->draw_pix(x, y, RGB888(255, 255, 255));
    }
    else {
        m_controller->clear();
    }
    m_controller->update();
}

