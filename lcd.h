#ifndef LCD_H
#define LCD_H

#include <QWidget>

#define LCD_PIX_ZOOM_IN         5
#define LCD_X_SIZE              128
#define LCD_Y_SIZE              64
#define LCD_PAGE_SIZE           8

#if (LCD_PIX_ZOOM_IN <= 1)
#undef  LCD_PIX_ZOOM_IN
#define LCD_PIX_ZOOM_IN         2
#endif

class lcd : public QWidget
{
    Q_OBJECT
public:
    explicit lcd(QWidget *parent = 0);
    void clear(void);
    void draw_pix(int xpos, int ypos, int color);
    void lcd_draw_bitmap(const unsigned char *pbitmap,
                         int xpos,
                         int ypos,
                         int bmap_width,
                         int bmap_height);
    void lcd_draw_text(int xpos,
                       int ypos,
                       const unsigned char *pstr);
private:
    quint8 lcd_buf[LCD_X_SIZE * LCD_Y_SIZE / 8];
signals:

public slots:

protected:
    void paintEvent(QPaintEvent *e);
};

#endif // LCD_H
