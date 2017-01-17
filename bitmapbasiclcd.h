#ifndef BITMAPBASICLCD_H
#define BITMAPBASICLCD_H

#define LCD_X_SIZE              128
#define LCD_Y_SIZE              64

class PlatformSurface;

class BitmapBasicLCD
{
public:
    BitmapBasicLCD();
    void clear(void);
    void draw_rect(int x, int y, int width, int height, int color);
private:
    void draw_pix(int xpos, int ypos, int color);
    void draw_line(int x0, int y0, int x1, int y1, int color);
    int lcdBpp;
    unsigned char *lcd_buf;
};

#endif // BITMAPBASICLCD_H
