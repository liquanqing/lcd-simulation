#include "bitmapbasiclcd.h"

#include <string.h>

#include "platformsurface.h"
#include "hostplatformsurface.h"

BitmapBasicLCD::BitmapBasicLCD()
{
}

void BitmapBasicLCD::clear()
{
    memset(lcd_buf, 0xaa, sizeof(lcd_buf));
    HostPlatformSurface::instance().surfaceSizeChanged(LCD_X_SIZE, LCD_Y_SIZE);
    HostPlatformSurface::instance().surfaceUpdated(lcd_buf, 0, 0, LCD_X_SIZE, LCD_Y_SIZE);
}

void BitmapBasicLCD::draw_pix(int xpos, int ypos, int color)
{
    lcd_buf[xpos + (LCD_X_SIZE * ypos)] = color;
}

void BitmapBasicLCD::draw_line(int x0, int y0, int x1, int y1, int color)
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

        distance = x_delta > y_delta ? x_delta:y_delta;

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

void BitmapBasicLCD::draw_rect(int x, int y, int width, int height, int color)
{
    int x0 = x;
    int y0 = y;
    int x1 = x + width - 1;
    int y1 = x + height - 1;
    draw_line(x0, y0, x0, y1, color);
    draw_line(x1, y0, x1, y1, color);
    draw_line(x0, y0, x1, y0, color);
    draw_line(x0, y1, x1, y1, color);
    HostPlatformSurface::instance().surfaceUpdated(lcd_buf, x, y, width, height);
}
