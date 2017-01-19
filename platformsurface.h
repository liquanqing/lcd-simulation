#ifndef PLATFORMSURFACE
#define PLATFORMSURFACE

enum ColorFormat {
    COLOR_FORMAT_RGB888,
    COLOR_FORMAT_RGB16
};

class PlatformSurface {
public:
    virtual ~PlatformSurface() {}
    virtual void setColorFormat(ColorFormat format) = 0;
    virtual void surfaceUpdated(const unsigned char *fb, int x, int y, int width, int height) = 0;
    virtual void surfaceSizeChanged(int width, int height) = 0;
};

#endif // PLATFORMSURFACE

