#include "BMP.h"
#include <string.h>
#include <math.h>

BMP::BMP() : Image()
{
    this->bfHeader = new bmpHeader();
}

BMP::~BMP()
{
    if (this->bfHeader) delete this->bfHeader;
}

void BMP::newPicture(int width, int height, int bitDepth)
{
    int paddingByte = 4;
    if (!this->bfHeader) {
        exit(0);
    }

    this->bfHeader->bfMagic.magicNum[0] = 'B';
    this->bfHeader->bfMagic.magicNum[1] = 'M';

    this->bfHeader->bfHeader.bfReserved1 = 0;
    this->bfHeader->bfHeader.bfReserved1 = 0;

    this->bfHeader->bfHeaderInfo.bfSize = sizeof(bmpHeaderInfo);
    this->bfHeader->bfHeaderInfo.bfWidth = width;
    this->bfHeader->bfHeaderInfo.bfHeight = height;
    this->bfHeader->bfHeaderInfo.bfPlane = 1;
    this->bfHeader->bfHeaderInfo.bfBitCount = bitDepth;
    this->bfHeader->bfHeaderInfo.bfCompress = BI_RGB;
    if ( bitDepth > 8){
        this->bfHeader->bfHeaderInfo.bfSizeImage =
            width * height * (bitDepth >> 3);
    } else {
        this->bfHeader->bfHeaderInfo.bfSizeImage =
            (width * height * (bitDepth >> 3) ) + 4 * ( 1 << bitDepth);
    }
    paddingByte -= ((bitDepth >> 3) * width) % 4;
    if (paddingByte == 4) paddingByte = 0;
    paddingByte *= height;

    this->bfHeader->bfHeaderInfo.bfSizeImage += 2 + paddingByte;


    this->bfHeader->bfHeaderInfo.bfXPelsPerMeter = 2834;
    this->bfHeader->bfHeaderInfo.bfYPelsPerMeter = 2834;
    this->bfHeader->bfHeaderInfo.bfClrUsed = 0;
    this->bfHeader->bfHeaderInfo.bfClrImportant = 0;

    this->bfHeader->bfHeader.bfOffset =   sizeof(bmpHeaderInfo)
                                        + sizeof(bmpHeaderStructure)
                                        + sizeof(bmpMagic);
    this->bfHeader->bfHeader.bfSize = this->bfHeader->bfHeaderInfo.bfSizeImage
                                      + this->bfHeader->bfHeader.bfOffset;

    this->pArray = new Pixel *[height];
    for (int i = height-1; i >= 0; i--){
        this->pArray[i] = new Pixel[width];
        for (int j = 0; j < width; j++){
            this->pArray[i][j].red = 200;
            this->pArray[i][j].green = 200;
            this->pArray[i][j].blue = 200;
        }
    }
}


int BMP::readPictureInfo(FILE * file)
{
    if (!file) return 0;
    fread( &this->bfHeader->bfMagic.magicNum[0], sizeof(char), 1, file);
    fread( &this->bfHeader->bfMagic.magicNum[1], sizeof(char), 1, file);
    if ( this->bfHeader->bfMagic.magicNum[0]  != 'B') return -1;
    if ( this->bfHeader->bfMagic.magicNum[1]  != 'M') return -1;
    fread( &this->bfHeader->bfHeader, sizeof(bmpHeaderStructure), 1, file);
    fread( &this->bfHeader->bfHeaderInfo, sizeof(bmpHeaderInfo), 1, file);

    if (this->bfHeader->bfHeaderInfo.bfBitCount == 16)
    {
        this->redMask   = 0x7C00;
        this->greenMask = 0x03E0;
        this->blueMask  = 0x001F;
        this->alphaMask = 0x8000;
    }
    return 1;
}

int BMP::writePictureInfo(FILE * file)
{
    if (!file) return 0;
    fwrite( &this->bfHeader->bfMagic.magicNum[0], sizeof(char), 1, file);
    fwrite( &this->bfHeader->bfMagic.magicNum[1], sizeof(char), 1, file);
    if ( this->bfHeader->bfMagic.magicNum[0]  != 'B') return -1;
    if ( this->bfHeader->bfMagic.magicNum[1]  != 'M') return -1;
    fwrite( &this->bfHeader->bfHeader, sizeof(bmpHeaderStructure), 1, file);
    fwrite( &this->bfHeader->bfHeaderInfo, sizeof(bmpHeaderInfo), 1, file);
    return 1;
}

unsigned char * BMP::getPictureInfo( void )
{
        return NULL;
}

void BMP::printPictureInfo( void )
{
    if (!this->bfHeader) return;
    fprintf(stdout, "Magic Number: %c%c\n",
            this->bfHeader->bfMagic.magicNum[0],
            this->bfHeader->bfMagic.magicNum[1]
            );
    fprintf(stdout,"Header Struct:\n");
    fprintf(stdout,"\tFile Size: %d\n", this->bfHeader->bfHeader.bfSize);
    fprintf(stdout,"\tReserved 1: %d\n", this->bfHeader->bfHeader.bfReserved1);
    fprintf(stdout,"\tReserved 2: %d\n", this->bfHeader->bfHeader.bfReserved2);
    fprintf(stdout,"\tOffset: %d\n", this->bfHeader->bfHeader.bfOffset);

    fprintf(stdout,"Header Info:\n");
    fprintf(stdout,"\tSize: %d\n\tWidth: %d\n\tHeight: %d\n\tPlanes: %d",
            this->bfHeader->bfHeaderInfo.bfSize,
            this->bfHeader->bfHeaderInfo.bfWidth,
            this->bfHeader->bfHeaderInfo.bfHeight,
            this->bfHeader->bfHeaderInfo.bfPlane);
    fprintf(stdout,"\n\tBit Count: %d\n\tCompression: %d\n\tSize Image: %d",
            this->bfHeader->bfHeaderInfo.bfBitCount,
            this->bfHeader->bfHeaderInfo.bfCompress,
            this->bfHeader->bfHeaderInfo.bfSizeImage);
    fprintf(stdout,"\n\tXPelsPerMeter: %d\n\tYPelsPerMeter: %d",
            this->bfHeader->bfHeaderInfo.bfXPelsPerMeter,
            this->bfHeader->bfHeaderInfo.bfYPelsPerMeter);
    fprintf(stdout,"\n\tClrUsed: %d\n\tClrImportant: %d\nEND",
            this->bfHeader->bfHeaderInfo.bfClrUsed,
            this->bfHeader->bfHeaderInfo.bfClrImportant);
}

int BMP::readPictureData(FILE * file)
{
    if (!file) return 0;
    if (!this->bfHeader) return 0;
    if (this->bfHeader->bfHeaderInfo.bfCompress != BI_RGB) return 0;

    int bytePadding = (this->getBitDepth() >> 3) * this->getWidth() % 4;
    bytePadding = 4 - bytePadding;
    if (bytePadding == 4) bytePadding = 0;
    unsigned char emptyByte = 0;

    fseek(file, this->bfHeader->bfHeader.bfOffset, SEEK_SET);

    this->pArray = new Pixel *[this->getHeight()];

    for (int i = this->getHeight() - 1; i >= 0; i--){
        this->pArray[i] = new Pixel[this->getWidth()];
        for (int j = 0; j < this->getWidth(); j++){

            if (this->getBitDepth() == 16)
            {
                unsigned char someChar = '0';
                unsigned char someChar_t = '0';
                unsigned short dw = 0;
                fread(&someChar_t, sizeof(char), 1, file);
                fread(&someChar, sizeof(char), 1, file);
                dw = someChar;

                dw = ((dw << 8) | someChar_t);
                this->pArray[i][j].blue  = ((dw & this->blueMask)) * 8;
                this->pArray[i][j].green = ((dw & this->greenMask) >> 5) * 8;
                this->pArray[i][j].red   = ((dw & this->redMask) >> 10) * 8;
            }
            else if (this->getBitDepth() == 24)
            {
                fread(&this->pArray[i][j].blue,sizeof(char), 1, file);
                fread(&this->pArray[i][j].green,sizeof(char), 1,file);
                fread(&this->pArray[i][j].red, sizeof(char), 1, file);
            }
            else if (this->getBitDepth() == 32)
            {
                fread(&this->pArray[i][j].blue,sizeof(char), 1, file);
                fread(&this->pArray[i][j].green,sizeof(char), 1,file);
                fread(&this->pArray[i][j].red, sizeof(char), 1, file);
                fread(&this->pArray[i][j].alpha, sizeof(char), 1, file);
            }
            else
            {

            }
        }
        for (int m = 0; m < bytePadding; m++){
            fread(&emptyByte, sizeof(char), 1, file);
        }
    }

    return 1;
}

int BMP::writePictureData(FILE * file)
{
    if (!file) return 0;
    if (!this->pArray) return 0;

    int bytePadding = (this->getBitDepth() >> 3) * this->getWidth() % 4;
    bytePadding = 4 - bytePadding;
    if (bytePadding == 4) bytePadding = 0;
    unsigned char emptyByte = 0x00;

    for (int i = this->getHeight() - 1; i >= 0; i--){
        for (int j = 0; j < this->getWidth(); j++){

            if (this->getBitDepth() == 16)
            {
                unsigned short bw = 0;
                unsigned char someChar = 0;

                someChar = this->pArray[i][j].red / 8;
                bw = ((bw | someChar) << 5);

                someChar = this->pArray[i][j].green / 8;
                bw = ((bw | someChar) << 5);

                someChar = this->pArray[i][j].blue / 8;
                bw = ((bw | someChar));

                fwrite(&bw, sizeof(short), 1, file);
            }
            else if (this->getBitDepth() == 24)
            {
                fwrite(&this->pArray[i][j].blue,sizeof(char), 1, file);
                fwrite(&this->pArray[i][j].green,sizeof(char), 1,file);
                fwrite(&this->pArray[i][j].red, sizeof(char), 1, file);
            }
            else if (this->getBitDepth() == 32)
            {
                fwrite(&this->pArray[i][j].blue,sizeof(char), 1, file);
                fwrite(&this->pArray[i][j].green,sizeof(char), 1,file);
                fwrite(&this->pArray[i][j].red, sizeof(char), 1, file);
                fwrite(&this->pArray[i][j].alpha, sizeof(char), 1, file);
            }
            else
            {

            }
        }
        for (int m = 0; m < bytePadding; m++){
            fwrite(&emptyByte, sizeof(char), 1, file);
        }
    }
    return 1;
}

int BMP::readPicture(const char * fileName)
{
    FILE * file = fopen(fileName, "rb");
    if (!file) return 0;
    if ( this->readPictureInfo(file) == 0){
        fclose(file);
        return 0;
    }
    if ( this->readPictureData(file) == 0) {
        fclose(file);
        return 0;
    }
    fclose(file);
    return 1;
}

int BMP::writePicture(const char * fileName)
{
    FILE * file = fopen(fileName, "wb");
    if ( this->writePictureInfo(file) == 0){
        fclose(file);
        return 0;
    }
    fseek(file, this->bfHeader->bfHeader.bfOffset, SEEK_SET);
    if ( this->writePictureData(file) == 0) {
        fclose(file);
        return 0;
    }
    fclose(file);
    return 1;
}

int BMP::getBitDepth( void )
{
    if (!this->bfHeader) return 0;
    return this->bfHeader->bfHeaderInfo.bfBitCount;
}

int BMP::getHeight( void )
{
    if (!this->bfHeader) return 0;
    return this->bfHeader->bfHeaderInfo.bfHeight;
}

int BMP::getWidth( void )
{
    if (!this->bfHeader) return 0;
    return this->bfHeader->bfHeaderInfo.bfWidth;
}


int BMP::setBitDepth( int bitDepth )
{
    if (!this->bfHeader) return 0;
    if (bitDepth != 16 && bitDepth != 24 && bitDepth != 32) return 0;
    int size = this->getWidth() * this->getHeight() * (bitDepth >> 3);
    int bytePadding = (this->getBitDepth() >> 3) * this->getWidth() % 4;
    bytePadding = 4 - bytePadding;
    if (bytePadding == 4) bytePadding = 0;
    size = size + (bytePadding * this->getHeight());
    this->bfHeader->bfHeaderInfo.bfBitCount = bitDepth;
    this->bfHeader->bfHeaderInfo.bfSizeImage = size;
    return 1;
}

int BMP::setWidth( int width )
{
    if (!this->bfHeader) return 0;
    int size = width * this->getHeight() * (this->getBitDepth() >> 3);
    int bytePadding = (this->getBitDepth() >> 3) * this->getWidth() % 4;
    bytePadding = 4 - bytePadding;
    if (bytePadding == 4) bytePadding = 0;
    size = size + (bytePadding * this->getHeight());

    Pixel ** pMatrix;
    pMatrix = new Pixel *[this->getHeight()];
    for (int i = this->getHeight() - 1; i >= 0; i--){
        pMatrix[i] = new Pixel[width];
        for (int j = 0; j < width; j++){
            if (j < this->getWidth()){
                pMatrix[i][j] = pArray[i][j];
            }
            else{
                pMatrix[i][j].alpha = 0;
                pMatrix[i][j].red = 255;
                pMatrix[i][j].green = 255;
                pMatrix[i][j].blue = 255;
            }
        }
    }
    pArray = pMatrix;

    this->bfHeader->bfHeaderInfo.bfSizeImage = size;
    this->bfHeader->bfHeaderInfo.bfWidth = width;
    return 1;
}

int BMP::setHeight( int height )
{
    if (!this->bfHeader) return 0;
    int size = this->getWidth() * height * (this->getBitDepth() >> 3);
    int bytePadding = (this->getBitDepth() >> 3) * this->getWidth() % 4;
    bytePadding = 4 - bytePadding;
    if (bytePadding == 4) bytePadding = 0;
    size = size + (bytePadding * height);

    Pixel ** pMatrix;
    pMatrix = new Pixel *[height];
    for (int i = height - 1; i >= 0; i--){
        pMatrix[i] = new Pixel[this->getWidth()];
        for (int j = 0; j < this->getWidth(); j++){
            if (i < this->getHeight()){
                pMatrix[i][j] = pArray[i][j];
            }
            else{
                pMatrix[i][j].alpha = 0;
                pMatrix[i][j].red = 255;
                pMatrix[i][j].green = 255;
                pMatrix[i][j].blue = 255;
            }
        }
    }
    pArray = pMatrix;
    this->bfHeader->bfHeaderInfo.bfSizeImage = size;
    this->bfHeader->bfHeaderInfo.bfHeight = height;
    return 1;
}
