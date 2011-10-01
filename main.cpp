#include <iostream>
#include "Image.h"
#include "BMP.h"
#include "Histogram.h"
using namespace std;

int main()
{
    Image * p = new BMP();
    p->readPicture("coloroflife.bmp");
    p->inversion();
    p->writePicture("asasasa.bmp");
    delete p;
    return 0;
}
