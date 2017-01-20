#ifndef UTILS_H
#define UTILS_H

enum ColorFormat {
    COLOR_FORMAT_RGB888,
    COLOR_FORMAT_RGB16
};

extern int bitsPerPixel(ColorFormat format);

#endif // UTILS_H
