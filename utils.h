#ifndef UTILS_H
#define UTILS_H

#define BUTTON_MASK_NONE    0x00000000
#define BUTTON_MASK_ALL     0x7FFFFFFF
#define BUTTON_MASK_LEFT    0x00000001
#define BUTTON_MASK_RIGHT   0x00000002
#define BUTTON_MASK_MID     0x00000004
#define BUTTON_MASK_BACK    0x00000008
#define BUTTON_MASK_FORWARD 0x00000010

enum ColorFormat {
    COLOR_FORMAT_RGB888,
    COLOR_FORMAT_RGB16
};

extern int bitsPerPixel(ColorFormat format);

#endif // UTILS_H
