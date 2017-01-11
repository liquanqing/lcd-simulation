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
    ~lcd();
    void clear(void);
    void draw_pix(int xpos, int ypos, int color);
    int  read_pix(int xpos, int ypos);
    void draw_line(int x0, int y0, int x1, int y1, int color);
    void draw_rect(int x0, int y0, int width, int height, int color);
    void draw_circle(int x0, int y0, int r, int color);
    void draw_round_rect(int x0, int y0, int width, int height, int rad, int color);

private:
    quint8 *lcd_buf;
signals:

public slots:

protected:
    void paintEvent(QPaintEvent *e);
};

#endif // LCD_H
