#include "lcd.h"
#include <QPainter>
#include <QPalette>
#include <QDebug>

lcd::lcd(QWidget *parent) : QWidget(parent)
{
    setFixedSize(LCD_X_SIZE * LCD_PIX_ZOOM_IN + 1, LCD_Y_SIZE * LCD_PIX_ZOOM_IN + 1);
}

void lcd::clear(void)
{
    memset(lcd_buf, 0, sizeof(lcd_buf));
    this->update();
}

void lcd::draw_pix(int xpos, int ypos, int color)
{
    quint8 page, page_bit;

    if (xpos >= LCD_X_SIZE) {
        xpos = LCD_X_SIZE - 1;
    }

    if (ypos >= LCD_Y_SIZE) {
        xpos = LCD_Y_SIZE - 1;
    }

    page = ypos / LCD_PAGE_SIZE;
    page_bit = ypos % LCD_PAGE_SIZE;

    if (color) {
        lcd_buf[xpos + (LCD_X_SIZE * page)] |= 1 << page_bit;
    } else {
        lcd_buf[xpos + (LCD_X_SIZE * page)] &= ~(1 << page_bit);
    }
}

void lcd::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.fillRect(QRect(0, 0, LCD_X_SIZE * LCD_PIX_ZOOM_IN + 1, LCD_Y_SIZE * LCD_PIX_ZOOM_IN + 1),
                     QBrush(Qt::blue));
    int x, y;

    painter.setPen(Qt::blue);
    painter.setBrush(QBrush(Qt::white));
    for (x = 0; x < LCD_X_SIZE * LCD_Y_SIZE / LCD_PAGE_SIZE; x ++) {
        for (y = 0; y < LCD_PAGE_SIZE; y++) {
            if (lcd_buf[x] & (1<<y)) {
                painter.drawRect((x % LCD_X_SIZE) * LCD_PIX_ZOOM_IN,
                                 ((x / LCD_X_SIZE * LCD_PAGE_SIZE) + y) * LCD_PIX_ZOOM_IN,
                                 LCD_PIX_ZOOM_IN,
                                 LCD_PIX_ZOOM_IN);
            }
        }
    }
}
