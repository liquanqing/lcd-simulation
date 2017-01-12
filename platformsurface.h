#ifndef PLATFORMSURFACE
#define PLATFORMSURFACE

class PlatformSurface {
public:
    virtual ~PlatformSurface() {}
    virtual void surfaceUpdated(const unsigned char *fb, int x, int y, int width, int height) = 0;
    virtual void surfaceSizeChanged(int width, int height) = 0;
};

#endif // PLATFORMSURFACE

