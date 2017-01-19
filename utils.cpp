#include "utils.h"

int bitsPerPixel(QImage::Format format)
{
    int ret = 0;
    switch (format) {
    case QImage::Format_RGB16:
        ret = 2;
        break;
    case QImage::Format_RGB888:
        ret = 4;
        break;
    default:
        break;
    }
    return ret;
}
