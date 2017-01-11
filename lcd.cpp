#include "lcd.h"
#include <QPainter>
#include <QPalette>
#include <QDebug>

#define ABS(A)      ((A > 0) ? A : (-A))
#define MAX(A,B)    ((A >= B) ? A : B)
#define MIN(A,B)    ((A <= B) ? A : B)

lcd::lcd(QWidget *parent) : QWidget(parent)
{
    int i;
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

void lcd::draw_line(int x0, int y0, int x1, int y1, int color)
{
    int t, distance;
    int x_err = 0, y_err = 0;
    int x_inc, y_inc;
    int row = x0, column = y0;
    int x_delta = x1 - x0;
    int y_delta = y1 - y0;

    if ((x0 == x1) && (y0 == y1)) {
        draw_pix(x0, y0, color);
    } else if (x0 == x1) {
        if (y0 > y1) {
            for (t = y0; t >= y1; t++) {
                draw_pix(x0, t, color);
            }
        } else {
            for (t = y0; t <= y1; t++) {
                draw_pix(x0, t, color);
            }
        }
    } else if (y0 == y1) {
        if (x0 > x1) {
            for (t = x0; t >= x1; t++) {
                draw_pix(t, y0, color);
            }
        } else {
            for (t = x0; t <= x1; t++) {
                draw_pix(t, y0, color);
            }
        }
    } else {
        if (x_delta > 0) {
            x_inc = 1;
        } else if (x_delta == 0) {
            x_inc = 0;
        } else {
            x_inc = -1;
            x_delta = -x_delta;
        }

        if (y_delta > 0) {
            y_inc = 1;
        } else if (y_delta == 0) {
            y_inc = 0;
        } else {
            y_inc = -1;
            y_delta = -y_delta;
        }

        distance = MAX(x_delta, y_delta);

        for (t = 0; t <= distance; t++) {
            draw_pix(row, column, color);

            x_err += x_delta + 1;
            y_err += y_delta + 1;

            if (x_err > distance) {
                x_err -= distance;
                row += x_inc;
            }

            if (y_err > distance) {
                y_err -= distance;
                column += y_inc;
            }
        }

    }
}

void lcd::draw_rect(int x, int y, int width, int height, int color)
{
    int x0 = x;
    int y0 = y;
    int x1 = x + width - 1;
    int y1 = x + height - 1;
    draw_line(x0, y0, x0, y1, color);
    draw_line(x1, y0, x1, y1, color);
    draw_line(x0, y0, x1, y0, color);
    draw_line(x0, y1, x1, y1, color);
}

void lcd::draw_circle(int x, int y, int r, int color)
{

}

void lcd::draw_circle_plot(int xc, int xy, int x, int y)
{
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
