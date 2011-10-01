#include "Histogram.h"

Histogram::Histogram()
{
    //ctor
}

Histogram::~Histogram()
{
    //dtor
}

Histogram::Histogram(Image * img)
{
    createHistogram(img);
}

void Histogram::createHistogram(Image * img)
{
    for (int i = 0; i <= 255; i++) {
        histoBlue [i] = 0;
        histoGreen[i] = 0;
        histoRed  [i] = 0;
        histoRGB  [i] = 0;
    }
    for(int i = img->getHeight() - 1; i >= 0 ; i--){
        for (int j = 0; j < img->getWidth(); j++){
            histoRed  [ img->getPixel(i,j)->red   ] += 1;
            histoGreen[ img->getPixel(i,j)->green ] += 1;
            histoBlue [ img->getPixel(i,j)->blue  ] += 1;
            int avgColor = img->getPixel(i,j)->blue + img->getPixel(i,j)->green
                           + img->getPixel(i,j)->red;
            histoRGB[(avgColor / 3)] +=1;
        }
    }
}

Image * Histogram::getHistoBlue()
{
    int max = 0;
    int aHisto[256];
    for (int i = 0; i < 255; i++) if (max < histoBlue[i]) max = histoBlue[i];
    if (max == 0){
        fprintf(stderr, "Divided by zero\n");
        exit(0);
    }
    memcpy(aHisto, histoBlue, sizeof(histoBlue));
    for (int i = 0; i < 255; i++) aHisto[i] = (histoBlue[i] * 100) / max;

    Image * histo = new BMP();
    histo->newPicture(255, 100);
    for (int i = histo->getHeight() - 1; i >= 0; i--){
        for (int j = 0; j < 256; j++){
            if (aHisto[j] == 0) continue;
            histo->setPixel(i,j, 0);
            aHisto[j] -= 1;
        }
    }

    return histo;
}

Image * Histogram::getHistoGreen()
{
    int max = 0;
    int aHisto[256];
    for (int i = 0; i < 255; i++) if (max < histoGreen[i]) max = histoGreen[i];

    if (max == 0){
        fprintf(stderr, "Divided by zero\n");
        exit(0);
    }
    memcpy(aHisto, histoBlue, sizeof(histoBlue));
    for (int i = 0; i < 255; i++) aHisto[i] = (histoGreen[i] * 100) / max;

    Image * histo = new BMP();
    histo->newPicture(255, 100);
    for (int i = histo->getHeight() - 1; i >= 0; i--){
        for (int j = 0; j < 256; j++){
            if (aHisto[j] == 0) continue;
            histo->setPixel(i,j, 0);
            aHisto[j] -= 1;
        }
    }
    return histo;
}

Image * Histogram::getHistoRed()
{
    int max = 0;
    int aHisto[256];
    for (int i = 0; i < 255; i++) if (max < histoRed[i]) max = histoRed[i];
    if (max == 0){
        fprintf(stderr, "Divided by zero\n");
        exit(0);
    }

    memcpy(aHisto, histoBlue, sizeof(histoBlue));
    for (int i = 0; i < 255; i++) aHisto[i] = (histoRed[i] * 100) / max;

    Image * histo = new BMP();
    histo->newPicture(255, 100);
    for (int i = histo->getHeight() - 1; i >= 0; i--){
        for (int j = 0; j < 256; j++){
            if (aHisto[j] == 0) continue;
            histo->setPixel(i,j, 0);
            aHisto[j] -= 1;
        }
    }
    return histo;
}

Image * Histogram::getHistoRGB()
{
    int max = 0;
    int aHisto[256];

    for (int i = 0; i < 255; i++) if (max < histoRGB[i]) max = histoRGB[i];

    if (max == 0){
        fprintf(stderr, "Divided by zero\n");
        exit(0);
    }
    memcpy(aHisto, histoBlue, sizeof(histoBlue));
    for (int i = 0; i < 255; i++) aHisto[i] = (histoRGB[i] * 100) / max;

    Image * histo = new BMP();
    histo->newPicture(255, 100);
    for (int i = histo->getHeight() - 1; i >= 0; i--){
        for (int j = 0; j < 256; j++){
            if (aHisto[j] == 0) continue;
            histo->setPixel(i,j, 0);
            aHisto[j] -= 1;
        }
    }
    return histo;
}

void Histogram::stepHistogram(Image * img, int value)
{
    Pixel * pix;
    for (int i = 0; i < img->getHeight(); i++){
        for (int j = 0; j < img->getWidth(); j++){
            pix = img->getPixel(i, j);
            if (pix->red + value <= 255 && pix->red + value >= 0)
                img->setPixel(i, j, pix->red + value);
            else if (pix->red + value > 255)
                img->setPixel(i, j, 255);
            else if (pix->red + value < 0)
                img->setPixel(i, j, 0);
        }
    }
}

void Histogram::stepHistogramRGB(Image * img, int value )
{
    Pixel * pix;
    for (int i = 0; i < img->getHeight(); i++){
        for (int j = 0; j < img->getWidth(); j++){
            pix = img->getPixel(i, j);
            if (pix->red + value <= 255 && pix->red + value >= 0)
                img->setPixel(i, j, pix->red + value, pix->green, pix->blue);
            else if (pix->red + value > 255)
                img->setPixel(i, j, 255, pix->green, pix->blue);
            else if (pix->red + value < 0)
                img->setPixel(i, j, 0, pix->green, pix->blue);

            if (pix->green + value <= 255 && pix->green + value >= 0)
                img->setPixel(i, j, pix->red, pix->green + value, pix->blue);
            else if (pix->green + value > 255)
                img->setPixel(i, j, pix->red, 255, pix->blue);
            else if (pix->green + value < 0)
                img->setPixel(i, j, pix->red, 0, pix->blue);

            if (pix->blue + value <= 255 && pix->blue + value >= 0)
                img->setPixel(i, j, pix->red, pix->green, pix->blue + value);
            else if (pix->blue + value > 255)
                img->setPixel(i, j, pix->red, pix->green, 255);
            else if (pix->blue + value < 0)
                img->setPixel(i, j, pix->red, pix->green, 0);
        }
    }
}

void Histogram::stepHistogramRed(Image * img, int value )
{
    Pixel * pix;
    for (int i = 0; i < img->getHeight(); i++){
        for (int j = 0; j < img->getWidth(); j++){
            pix = img->getPixel(i, j);
            if (pix->red + value <= 255 && pix->red + value >= 0)
                img->setPixel(i, j, pix->red + value, pix->green, pix->blue);
            else if (pix->red + value > 255)
                img->setPixel(i, j, 255, pix->green, pix->blue);
            else if (pix->red + value < 0)
                img->setPixel(i, j, 0, pix->green, pix->blue);
        }
    }
}

void Histogram::stepHistogramGreen(Image * img, int value )
{
    Pixel * pix;
    for (int i = 0; i < img->getHeight(); i++){
        for (int j = 0; j < img->getWidth(); j++){
            pix = img->getPixel(i, j);
            if (pix->green + value <= 255 && pix->green + value >= 0)
                img->setPixel(i, j, pix->red, pix->green + value, pix->blue);
            else if (pix->green + value > 255)
                img->setPixel(i, j, pix->red, 255, pix->blue);
            else if (pix->green + value < 0)
                img->setPixel(i, j, pix->red, 0, pix->blue);
        }
    }
}

void Histogram::stepHistogramBlue(Image * img, int value )
{
    Pixel * pix;
    for (int i = 0; i < img->getHeight(); i++){
        for (int j = 0; j < img->getWidth(); j++){
            pix = img->getPixel(i, j);
            if (pix->blue + value <= 255 && pix->blue + value >= 0)
                img->setPixel(i, j, pix->red, pix->green, pix->blue + value);
            else if (pix->blue + value > 255)
                img->setPixel(i, j, pix->red, pix->green, 255);
            else if (pix->blue + value < 0)
                img->setPixel(i, j, pix->red, pix->green, 0);
        }
    }
}

void Histogram::stretchHistogram(Image * img, int value)
{
    Pixel * pix;
    if (value <= 0) return;
    for (int i = 0; i < img->getHeight(); i++){
        for (int j = 0; j < img->getWidth(); j++){
            pix = img->getPixel(i, j);
            if (pix->red * value <= 255 && pix->red * value >= 0)
                img->setPixel(i, j, pix->red * value);
            else if (pix->red * value > 255)
                img->setPixel(i, j, 255);
            else if (pix->red * value < 0)
                img->setPixel(i, j, 0);
        }
    }
}

void Histogram::stretchHistogramRGB(Image * img, int value )
{
    Pixel * pix;
    if (value <= 0) return;
    for (int i = 0; i < img->getHeight(); i++){
        for (int j = 0; j < img->getWidth(); j++){
            pix = img->getPixel(i, j);
            if (pix->red * value <= 255 && pix->red * value >= 0)
                img->setPixel(i, j, pix->red * value, pix->green, pix->blue);
            else if (pix->red * value > 255)
                img->setPixel(i, j, 255, pix->green, pix->blue);
            else if (pix->red * value < 0)
                img->setPixel(i, j, 0, pix->green, pix->blue);

            if (pix->green * value <= 255 && pix->green * value >= 0)
                img->setPixel(i, j, pix->red, pix->green * value, pix->blue);
            else if (pix->green * value > 255)
                img->setPixel(i, j, pix->red, 255, pix->blue);
            else if (pix->green * value < 0)
                img->setPixel(i, j, pix->red, 0, pix->blue);

            if (pix->blue * value <= 255 && pix->blue * value >= 0)
                img->setPixel(i, j, pix->red, pix->green, pix->blue * value);
            else if (pix->blue * value > 255)
                img->setPixel(i, j, pix->red, pix->green, 255);
            else if (pix->blue * value < 0)
                img->setPixel(i, j, pix->red, pix->green, 0);
        }
    }
}

void Histogram::stretchHistogramRed(Image * img, int value )
{
    if (value <= 0) return;
    Pixel * pix;
    for (int i = 0; i < img->getHeight(); i++){
        for (int j = 0; j < img->getWidth(); j++){
            pix = img->getPixel(i, j);
            if (pix->red * value <= 255 && pix->red * value >= 0)
                img->setPixel(i, j, pix->red * value, pix->green, pix->blue);
            else if (pix->red * value > 255)
                img->setPixel(i, j, 255, pix->green, pix->blue);
            else if (pix->red * value < 0)
                img->setPixel(i, j, 0, pix->green, pix->blue);
        }
    }
}

void Histogram::stretchHistogramGreen(Image * img, int value )
{
    if (value <= 0) return;
    Pixel * pix;
    for (int i = 0; i < img->getHeight(); i++){
        for (int j = 0; j < img->getWidth(); j++){
            pix = img->getPixel(i, j);
            if (pix->green * value <= 255 && pix->green * value >= 0)
                img->setPixel(i, j, pix->red, pix->green * value, pix->blue);
            else if (pix->green * value > 255)
                img->setPixel(i, j, pix->red, 255, pix->blue);
            else if (pix->green * value < 0)
                img->setPixel(i, j, pix->red, 0, pix->blue);
        }
    }
}

void Histogram::stretchHistogramBlue(Image * img, int value )
{
    if (value <= 0) return;
    Pixel * pix;
    for (int i = 0; i < img->getHeight(); i++){
        for (int j = 0; j < img->getWidth(); j++){
            pix = img->getPixel(i, j);
            if (pix->blue * value <= 255 && pix->blue * value >= 0)
                img->setPixel(i, j, pix->red, pix->green, pix->blue * value);
            else if (pix->blue * value > 255)
                img->setPixel(i, j, pix->red, pix->green, 255);
            else if (pix->blue * value < 0)
                img->setPixel(i, j, pix->red, pix->green, 0);
        }
    }
}

int Histogram::leftValue(int histo[])
{
    for (int i = 0; i < 256; i++) if ( histo[i] != 0 ) return i;
    return 0;
}

int Histogram::rightValue(int histo[])
{
    for (int i = 255; i>= 0; i--) if ( histo[i] != 0) return i;
    return 0;
}

void Histogram::editHistogram(Image * img)
{
    int histoLeft[256];
    int histoRight[256];
    memcpy(histoLeft, this->histoRed, sizeof(this->histoRed));
    int left = leftValue(histoLeft);
    this->stepHistogram(img, -left);
    for(int i = img->getHeight() - 1; i >= 0 ; i--){
        for (int j = 0; j < img->getWidth(); j++){
            histoRight  [ img->getPixel(i,j)->red   ] += 1;
        }
    }
    int right= rightValue(histoRight);
    this->stretchHistogram(img, right);
}
