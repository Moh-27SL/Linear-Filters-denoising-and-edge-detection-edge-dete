#include <iostream>
#include "Linear_filters.h"
#include "header/png.h"

using namespace std;

int main()
{
    PngImage img = load_png("result/shape.png");

    img.data = EdgeDetectorSteered(img.data,img.height,img.width,3,0.5,0.7854);

    save_png("result/Edge_sec_45.png",img);
    return 0;
}
