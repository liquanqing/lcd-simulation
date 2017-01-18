#include "workthread.h"

WorkThread::WorkThread(QObject *parent) : QObject(parent)
{
}

void WorkThread::initialize()
{
    moveToThread(&m_thread);
    m_thread.start();
}

void WorkThread::finalize()
{
    m_thread.quit();
    m_thread.wait();
}

void WorkThread::drawRectSlot()
{
    m_controller.clear();
    //m_controller.draw_rect(0, 0, 128, 64, 0xFF);
    m_controller.draw_circle(50, 30, 30, 0xFF);
    //m_controller.draw_round_rect(3, 3, 20, 10, 3, 0xFF);
//        //m_controller->draw_rect(1, 1, 126, 62, 1);
//        m_controller->draw_rect(2, 2, 124, 60, 1);
//        //m_controller->draw_rect(3, 3, 122, 58, 1);
//        m_controller->draw_rect(4, 4, 120, 56, 1);
//        //m_controller->draw_rect(5, 5, 118, 54, 1);
//        m_controller->draw_rect(6, 6, 116, 52, 1);
//        //m_controller->draw_rect(7, 7, 114, 50, 1);
//        m_controller->draw_rect(8, 8, 112, 48, 1);
//        //m_controller->draw_rect(9, 9, 110, 46, 1);
//        m_controller->draw_rect(10, 10, 108, 44, 1);
//        //m_controller->draw_rect(11, 11, 106, 42, 1);
//        m_controller->draw_rect(12, 12, 104, 40, 1);
//        //m_controller->draw_rect(13, 13, 102, 38, 1);
//        m_controller->draw_rect(14, 14, 100, 36, 1);
//        //m_controller->draw_rect(15, 15,  98, 34, 1);
//        m_controller->draw_rect(16, 16,  96, 32, 1);
//        //m_controller->draw_rect(17, 17,  94, 30, 1);
//        m_controller->draw_rect(18, 18,  92, 28, 1);
//        //m_controller->draw_rect(19, 19,  90, 26, 1);
//        m_controller->draw_rect(20, 20,  88, 24, 1);
//        //m_controller->draw_rect(21, 21,  86, 22, 1);
//        m_controller->draw_rect(22, 22,  84, 20, 1);
//        //m_controller->draw_rect(23, 23,  82, 18, 1);
//        m_controller->draw_rect(24, 24,  80, 16, 1);
//        //m_controller->draw_rect(25, 25,  78, 14, 1);
//        m_controller->draw_rect(26, 26,  76, 12, 1);
//       // m_controller->draw_rect(27, 27,  74, 10, 1);
//        m_controller->draw_rect(28, 28,  72, 8, 1);
//        //m_controller->draw_rect(29, 29,  70, 6, 1);
//        m_controller->draw_rect(30, 30,  68, 4, 1);
//        //m_controller->draw_rect(31, 31,  66, 2, 1);
}

