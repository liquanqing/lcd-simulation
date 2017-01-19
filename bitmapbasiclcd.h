#ifndef BITMAPBASICLCD_H
#define BITMAPBASICLCD_H

class PlatformSurface;

class BitmapBasicLCD
{
public:
    BitmapBasicLCD(PlatformSurface *surface, int width, int height, int bpp);
    ~BitmapBasicLCD();
    void clear(void);
    void draw_pix(int xpos, int ypos, int color);
    int read_pix(int xpos, int ypos);
    void draw_line(int x0, int y0, int x1, int y1, int color);
    void draw_rect(int x, int y, int width, int height, int color);
    void draw_circle(int x0, int y0, int r, int color);
    void draw_round_rect(int x0, int y0, int width, int height, int rad, int color);
private:
    int lcdBpp;
    int lcdXSize;
    int lcdYSize;
    unsigned char *lcd_buf;
    PlatformSurface *m_surface;
};

#endif // BITMAPBASICLCD_H
