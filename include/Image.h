#ifndef IMAGE_H
#define IMAGE_H

#include <stdio.h>
#include <stdlib.h>
#include "Pixel.h"

class Image
{
    public:
        Image( void );
        virtual ~Image( void );
        virtual void newPicture(int width, int height, int bitDepth = 24) = 0;
        virtual int readPicture(const char * fileName) = 0;
        virtual int writePicture(const char * fileName) = 0;
        virtual int readPictureInfo(FILE * file) = 0;
        virtual int writePictureInfo(FILE * file) = 0;
        virtual int readPictureData(FILE * file) = 0;
        virtual int writePictureData(FILE * file) = 0;
        virtual unsigned char * getPictureInfo( void ) = 0;
        virtual void printPictureInfo( void ) = 0;

        virtual int getBitDepth( void ) = 0;
        virtual int setBitDepth( int bitDepth ) = 0;

        virtual int getWidth( void ) = 0;
        virtual int setWidth( int width ) = 0;

        virtual int getHeight( void ) = 0;
        virtual int setHeight( int height ) = 0;

        Pixel * getPixel(int row, int col);

        int setPixel(int row, int col, Pixel * pix);
        int setPixel(int row, int col,
                              int R,
                              int G,
                              int B,
                              int A = 0);
        int setPixel(int row, int col, int G);

        void inversion();
        void createBorder(int length, Color * color);
        void createBorder(int top, int left, Color * color);
        void createBorder(int left, int right, int top, int bottom, Color * color);

    protected:

        Pixel **pArray;
        Pixel **pOriArray;
};

#endif // IMAGE_H
