#ifndef BITMAPBASICLCD_H
#define BITMAPBASICLCD_H

#define LCD_X_SIZE              800
#define LCD_Y_SIZE              480

class PlatformSurface;

class BitmapBasicLCD
{
public:
    BitmapBasicLCD(PlatformSurface *surface);
    void clear(void);
    void draw_rect(int x, int y, int width, int height, int color);
private:
    void draw_pix(int xpos, int ypos, int color);
    void draw_line(int x0, int y0, int x1, int y1, int color);
    unsigned char lcd_buf[LCD_X_SIZE * LCD_Y_SIZE * 2];
    PlatformSurface *m_surface;
};

#endif // BITMAPBASICLCD_H
