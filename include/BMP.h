#include "Image.h"

#ifndef BMP_H
#define BMP_H

/*  File Header Structure.
*  2   Type;       File Type Identifier
*  4   FileSize;   Size of File
*  2   Reserved1;  Reserved (should be 0)
*  2   Reserved2;  Reserved (should be 0)
*  4   Offset;     Offset to bitmap data
*  14    TOTAL
*/

struct FileBMPMagicNumber {
    unsigned char magicNum[2]; //Type
};
typedef struct FileBMPMagicNumber bmpMagic;

struct FileBMPHeaderStructure {
    unsigned int bfSize;
    unsigned short int bfReserved1;
    unsigned short int bfReserved2;
    unsigned int bfOffset;
};
typedef struct FileBMPHeaderStructure bmpHeaderStructure;

/*  Information Header Structure.
*  4  Size;            Size of Remaining Header
*  4  Width;           Width of Bitmap in Pixels
*  4  Height;          Height of Bitmap in Pixels
*  2  Planes;          Number of Planes
*  2  BitCount;        Bits Per Pixel
*  4  Compression;     Compression Scheme
*  4  SizeImage;       Size of bitmap
*  4  XPelsPerMeter;   Horz. Resolution in Pixels/Meter
*  4  YPelsPerMeter;   Vert. Resolution in Pixels/Meter
*  4  ClrUsed;         Number of Colors in Color Table
*  4  ClrImportant;    Number of Important Colors
*  40   TOTAL - Only support V3
*/
struct FileBMPHeaderInfo {
    unsigned int bfSize;
    unsigned int bfWidth;
    unsigned int bfHeight;
    unsigned short int bfPlane;
    unsigned short int bfBitCount;
    unsigned int bfCompress;
    unsigned int bfSizeImage;
    unsigned int bfXPelsPerMeter;
    unsigned int bfYPelsPerMeter;
    unsigned int bfClrUsed;
    unsigned int bfClrImportant;
};
typedef struct FileBMPHeaderInfo bmpHeaderInfo;

enum {
    BI_RGB,
    BI_RLE8,
    BI_RLE4,
    BI_BITFIELDS,
    BI_JPEG,
    BI_PNG,
};

struct FileBMPHeader {
    bmpMagic bfMagic;
    bmpHeaderStructure bfHeader;
    bmpHeaderInfo bfHeaderInfo;
};
typedef struct FileBMPHeader bmpHeader;

class BMP : public Image
{
    public:

        BMP();

        virtual ~BMP();

        virtual void newPicture(int width, int height, int bitDepth = 24);

        /**  Open the the file for reading. It must exists.
        *   Also reads the file header and image content
        *   @param fileName is name of the file
        *   @return 0 if could not open the file or file not exists.
        *   @return 1 if completed reads the file
        */
        virtual int readPicture(const char * fileName);

        /** Create a new file for writing bitmap header and image content.
        *   If the file exists will be replaced.
        *   @param fileName is name of the file
        *   @return 0 if cound not open the file
        *   @return 1 if completed writes the file
        */
        virtual int writePicture(const char * fileName);

        virtual int readPictureInfo(FILE * file);
        virtual int readPictureData(FILE * file);
        virtual int writePictureInfo(FILE * file);
        virtual int writePictureData(FILE * file);

        virtual unsigned char * getPictureInfo( void );

        /** Print the image header to console window.
        *   Bitmap file header must be read.
        */
        virtual void printPictureInfo( void );

        /** Read picture header and return bit depth of the image.
        *   @return 0 if header info must exists.
        *   @return 1 if any.
        */
        virtual int getBitDepth( void );


        virtual int setHeight( int height );
        virtual int setWidth( int width );
        virtual int setBitDepth( int bitDepth );

        /** Read picture header and return width of the image.
        *   @return 0 if header info must exists.
        *   @return width if any.
        */
        virtual int getWidth( void );

        /** Read picture header and return height of the image.
        *   @return 0 if header info must exists.
        *   @return height if any.
        */
        virtual int getHeight( void );


    protected:

        bmpHeader * bfHeader;
        int redMask, greenMask, blueMask, alphaMask;
};

#endif // BMP_H
