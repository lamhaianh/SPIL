#ifndef PIXEL_H
#define PIXEL_H

struct RGBAPixel{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char alpha;
};

typedef struct RGBAPixel Pixel;
typedef struct RGBAPixel Color;
#endif // PIXEL_H
