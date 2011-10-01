#ifndef HISTOGRAM_H
#define HISTOGRAM_H
#include "Image.h"
#include "BMP.h"
#include <string.h>
class Histogram
{
    public:
        Histogram();
        Histogram(Image * img);
        void createHistogram(Image * img);

        Image * getHistoRGB();
        Image * getHistoRed();
        Image * getHistoGreen();
        Image * getHistoBlue();

        void stepHistogram(Image * img, int value);
        void stepHistogramRGB(Image * img, int value);
        void stepHistogramRed(Image * img, int value);
        void stepHistogramGreen(Image * img, int value);
        void stepHistogramBlue(Image * img, int value);

        void stretchHistogram(Image * img, int value);
        void stretchHistogramRGB(Image * img, int value);
        void stretchHistogramRed(Image * img, int value);
        void stretchHistogramGreen(Image * img, int value);
        void stretchHistogramBlue(Image * img, int value);

        void editHistogram(Image * img);
        void editHistogramRed(Image * img);
        void editHistogramGreen(Image * img);
        void editHistogramBlue(Image * img);

        void equalizationHistogram(Image * img);
        void equalizationHistogramRed(Image * img);
        void equalizationHistogramGreen(Image * img);
        void equalizationHistogramBlue(Image * img);
        void equalizationHistogramRGB(Image * img);

        virtual ~Histogram();
    protected:
        int leftValue(int arr[]);
        int rightValue(int arr[]);

        int histoRGB[256], histoRed[256], histoBlue[256], histoGreen[256];

};

#endif // HISTOGRAM_H
