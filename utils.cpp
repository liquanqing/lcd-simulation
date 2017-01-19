#include "utils.h"

int bitsPerPixel(ColorFormat format)
{
    int ret = 0;
    switch (format) {
    case COLOR_FORMAT_RGB16:
        ret = 2;
        break;
    case COLOR_FORMAT_RGB888:
        ret = 4;
        break;
    default:
        break;
    }
    return ret;
}
