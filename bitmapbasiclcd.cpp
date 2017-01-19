#include "bitmapbasiclcd.h"

#include <string.h>
#include <new>

#include "platformsurface.h"

BitmapBasicLCD::BitmapBasicLCD(PlatformSurface *surface, int width, int height, int bpp)
    :lcdBpp(bpp)
    ,lcdXSize(width)
    ,lcdYSize(height)
    ,m_surface(surface)
{
    lcd_buf = new(std::nothrow) unsigned char[lcdXSize * lcdYSize * lcdBpp];
}

BitmapBasicLCD::~BitmapBasicLCD()
{
    delete lcd_buf;
}

void BitmapBasicLCD::clear()
{
    memset(lcd_buf, 0x00, lcdXSize * lcdYSize * lcdBpp);
    m_surface->surfaceSizeChanged(lcdXSize, lcdYSize);
}

void BitmapBasicLCD::draw_pix(int xpos, int ypos, int color)
{
    if (NULL == lcd_buf) {
        return;
    }

    if ((xpos > lcdXSize) || (ypos > lcdYSize)) {
            return;
        }

        switch(lcdBpp) {
        case 1:
            lcd_buf[xpos + (lcdXSize * ypos)] = (unsigned char)color;
            break;
        case 2:
            lcd_buf[(xpos + lcdXSize * ypos) * lcdBpp] = (color & 0xFF00) >> 8;
            lcd_buf[(xpos + lcdXSize * ypos) * lcdBpp + 1] = color & 0xFF;
            break;
        case 4:
            lcd_buf[(xpos + lcdXSize * ypos) * lcdBpp + 0] = color & 0xFF;
            lcd_buf[(xpos + lcdXSize * ypos) * lcdBpp + 1] = (color & 0xFF00) >> 8;
            lcd_buf[(xpos + lcdXSize * ypos) * lcdBpp + 2] = (color & 0xFF0000) >> 16;
            lcd_buf[(xpos + lcdXSize * ypos) * lcdBpp + 3] = (color & 0xFF000000) >> 24;
            break;
        default:
            lcd_buf[xpos + (lcdXSize * ypos)] = color;
            break;
        }
}

int BitmapBasicLCD::read_pix(int xpos, int ypos)
{
    if (NULL == lcd_buf) {
        return 0;
    }

    if ((xpos >= lcdXSize) || (ypos >= lcdYSize)) {
        return 0;
    }

    int color = 0;

    switch(lcdBpp) {
    case 1:
        color = lcd_buf[xpos + (lcdXSize * ypos)];
        break;
    case 2:
        color = lcd_buf[(xpos + lcdXSize * ypos) * lcdBpp] << 8;
        color |= lcd_buf[(xpos + lcdXSize * ypos) * lcdBpp + 1];
        break;
    case 4:
        color = lcd_buf[(xpos + lcdXSize * ypos) * lcdBpp + 3] << 24;
        color |= lcd_buf[(xpos + lcdXSize * ypos) * lcdBpp + 2] << 16;
        color |= lcd_buf[(xpos + lcdXSize * ypos) * lcdBpp + 1] << 8;
        color |= lcd_buf[(xpos + lcdXSize * ypos) * lcdBpp + 0] << 0;
        break;
    default:
        color = lcd_buf[xpos + (lcdXSize * ypos)];
        break;
    }

    return color;
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

    m_surface->surfaceUpdated(lcd_buf, x, y, width, height);
}

void BitmapBasicLCD::draw_circle(int x0, int y0, int r, int color)
{
    int x = 0, y = r;
    int delta = 1 - r;

    while (y >= x) {
        draw_pix(x + x0, y + y0, color);
        draw_pix(y + x0, x + y0, color);
        draw_pix(-x + x0, y + y0, color);
        draw_pix(-y + x0, x + y0, color);

        draw_pix(-x + x0, -y + y0, color);
        draw_pix(-y + x0, -x + y0, color);
        draw_pix(x + x0, -y + y0, color);
        draw_pix(y + x0, -x + y0, color);

        if (delta < 0) {
            delta = delta + 4 * x + 6;
        } else {
            delta = delta + 4 * (x - y) + 10;
            y --;
        }

        x ++;
    }

    m_surface->surfaceUpdated(lcd_buf, 0, 0, lcdXSize, lcdYSize);
}

void BitmapBasicLCD::draw_round_rect(int x0, int y0, int width, int height, int rad, int color)
{
    int x = 0, y = rad;
    int delta = 1 - rad;

    draw_line(x0 + rad, y0, x0 + width - rad, y0, color);
    draw_line(x0 + rad, y0 + height, x0 + width - rad, y0 + height, color);

    draw_line(x0, y0 + rad, x0, y0 + height - rad, color);
    draw_line(x0 + width, y0 + rad, x0 + width, y0 + height - rad, color);

    while (y >= x) {
        draw_pix(x + x0 + width - rad, y + y0 + height - rad, color);
        draw_pix(y + x0 + width - rad, x + y0 + height - rad, color);

        draw_pix(-x + x0 + rad, y + y0 + height - rad, color);
        draw_pix(-y + x0 + rad, x + y0 + height - rad, color);

        draw_pix(-x + x0 + rad, -y + y0 + rad, color);
        draw_pix(-y + x0 + rad, -x + y0 + rad, color);

        draw_pix(x + x0 + width - rad, -y + y0 + rad, color);
        draw_pix(y + x0 + width - rad, -x + y0 + rad, color);

        if (delta < 0) {
            delta = delta + 4 * x + 6;
        } else {
            delta = delta + 4 * (x - y) + 10;
            y --;
        }

        x ++;
    }

    m_surface->surfaceUpdated(lcd_buf, 0, 0, lcdXSize, lcdYSize);
}
