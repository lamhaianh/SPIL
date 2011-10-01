#include "Image.h"

Image::Image()
{

}

Image::~Image()
{
    if (this->pOriArray) {delete * pOriArray; delete * pArray;}

}

void Image::inversion()
{
    for (int i = 0; i < this->getHeight(); i++){
        for (int j = 0; j < this->getWidth(); j++){
            this->pArray[i][j].red = 255 - this->pArray[i][j].red;
            this->pArray[i][j].green = 255 - this->pArray[i][j].green;
            this->pArray[i][j].blue = 255 - this->pArray[i][j].blue;
        }
    }
}

Pixel * Image::getPixel(int row, int col){
    if (row < 0 || col < 0) return NULL;
    if (row >= this->getHeight() || col >= this->getWidth()) return NULL;
    Pixel * p = new Pixel();
    p->blue = this->pArray[row][col].blue;
    p->green = this->pArray[row][col].green;
    p->red = this->pArray[row][col].red;
    return p;
}

int Image::setPixel(int row, int col, Pixel * pix)
{
    if (row < 0 || col < 0) return 0;
    if (row >= this->getHeight() || col >= this->getWidth()) return 0;

    this->pArray[row][col].alpha = pix->alpha;
    this->pArray[row][col].blue  = pix->blue;
    this->pArray[row][col].green = pix->green;
    this->pArray[row][col].red   = pix->red;
    return 1;
}

int Image::setPixel(int row, int col,
                  int R,
                  int G,
                  int B,
                  int A)
{
    if (row < 0 || col < 0) return 0;
    if (row >= this->getHeight() || col >= this->getWidth()) return 0;
    this->pArray[row][col].alpha = A;
    this->pArray[row][col].blue  = B;
    this->pArray[row][col].green = G;
    this->pArray[row][col].red   = R;
    return 1;
}

int Image::setPixel(int row, int col, int Gr)
{
    if (row < 0 || col < 0) return 0;
    if (Gr < 0 || Gr > 255) return 0;
    if (row >= this->getHeight() || col >= this->getWidth()) return 0;

    this->pArray[row][col].blue  = (unsigned char)Gr;
    this->pArray[row][col].green = (unsigned char)Gr;
    this->pArray[row][col].red   = (unsigned char)Gr;
    return 1;
}

void Image::createBorder(int length, Color * color)
{

}
