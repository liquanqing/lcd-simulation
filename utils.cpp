#include "utils.h"

int bitsPerPixel(ColorFormat format)
{
    int ret = 1;
    switch (format) {
    case COLOR_FORMAT_RGB16:
        ret = 2;
        break;
    case COLOR_FORMAT_RGB888:
        ret = 3;
        break;
    default:
        break;
    }
    return ret;
}
