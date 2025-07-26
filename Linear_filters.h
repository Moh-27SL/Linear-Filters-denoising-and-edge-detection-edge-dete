#ifndef LINEAR_FILTERS_H_INCLUDED
#define LINEAR_FILTERS_H_INCLUDED

#include <vector>
#include <math.h>

unsigned char* img_conv(unsigned char* img, int img_height, int img_width, std::vector<double> kernel, int kernal_length)
{

    ///resulting image of convelution
    unsigned char* result = new unsigned char[img_height * img_width];

    for(int img_r=0; img_r < img_height; img_r++)
    {
        for(int img_c=0; img_c < img_width; img_c++)
        {
            int img_index = img_c + (img_r * img_width);
            double sum = 0;

            for(int H_r =0; H_r < kernal_length; H_r++)
            {
                for(int H_c =0; H_c < kernal_length; H_c++)
                {
                    int imgCol =  H_c + img_c;
                    int imgRow = H_r + img_r;

                    ///clamping of image when going out of bound
                    int imgInd;
                    if(imgCol >= img_width && imgRow >= img_height)
                        /// outside last row and last col
                        imgInd = (img_width - 1) + (img_height - 1) * img_width;

                    else if(imgCol >= img_width)
                        ///outside last col only
                        imgInd = (img_width - 1) + imgRow * img_width;

                    else if(imgRow >= img_height)
                        ///outside last row only
                        imgInd = imgCol + (img_height - 1) * img_width;

                    else
                        ///within bounds
                        imgInd = imgCol + imgRow * img_width;


                    int kernInd = H_c + H_r * kernal_length;
                    sum += img[imgInd] * kernel[kernInd];
                }
            }

            result[img_index] = static_cast<unsigned char> (sum + 0.5);
        }
    }

    return result;

}

///used for blurring and for smoothing
unsigned char* moving_avrg(unsigned char* img, int img_height, int img_width, int kernal_length)
{
    std::vector<double> kernal(kernal_length*kernal_length ,
                               1.0 / (kernal_length*kernal_length));

    return img_conv(img, img_height, img_width, kernal, kernal_length);
}

///pixels as far as 3 * sigma from the center of the kernal has affect on image
///////////////////////////////////////////////////////////////////
///must choose sigma according to kernal size and above equation/// 3 * sigma = 1/2 kernal_length, more than that equal 0
//////////////////////////////////////////////////////////////////
unsigned char* gaussian(unsigned char* img, int img_height, int img_width, int kernal_length, double sigma)
{
    std::vector<double> kernal(kernal_length*kernal_length);
    int mid = (kernal_length - 1) / 2;
    double sum =0;

    for(int r=0; r < kernal_length; r++)
    {
        for(int c=0; c<kernal_length; c++)
        {
            int y = mid - r;
            int x = c - mid;

            kernal[c + (r * kernal_length)] = ( 1/(2 * 3.1415926 * sigma * sigma) )
                                              * pow( 2.71828182, -( ( x*x + y*y ) /( 2* sigma * sigma ) ));

            sum += kernal[c + (r * kernal_length)];
        }
    }
    ///if sum must be close to 1
    std::cout<<"Kernal Sum of elements = "<< sum<<"\n";

    return img_conv(img, img_height, img_width, kernal, kernal_length);
}

///theta must be in RADIANS
std::vector<double> kernal_first_order_steered_gaussian(int kernal_length, double sigma, double theta)
{
    std::vector<double> Gtheta(kernal_length*kernal_length);

    int mid = (kernal_length - 1) / 2;
    for(int r=0; r < kernal_length; r++)
    {
        for(int c=0; c<kernal_length; c++)
        {
            int y = mid - r;
            int x = c - mid;
            double Gx, Gy;

            Gx = ( (-1*x) / (sigma * sigma) )
                                              * pow( 2.71828182, -( ( x*x + y*y ) /( 2* sigma * sigma ) ));

            Gy = ( (-1*y) / (sigma * sigma) )
                                              * pow( 2.71828182, -( ( x*x + y*y ) /( 2* sigma * sigma ) ));

            Gtheta[c + (r * kernal_length)] = Gx * cos(theta) + Gy * sin(theta);
        }
    }
    return Gtheta;
}

///theta must be in RADIANS
std::vector<double> kernal_second_order_steered_gaussian(int kernal_length, double sigma, double theta)
{
    std::vector<double> Gtheta(kernal_length*kernal_length);

    int mid = (kernal_length - 1) / 2;
    for(int r=0; r < kernal_length; r++)
    {
        for(int c=0; c<kernal_length; c++)
        {
            int y = mid - r;
            int x = c - mid;
            double Gxx, Gyy, Gxy;

            Gxx = ( (x*x - sigma*sigma) / pow(sigma, 4) )
                                              * pow( 2.71828182, -( ( x*x + y*y ) /( 2* sigma * sigma ) ));

            Gyy = ( (y*y - sigma*sigma) / pow(sigma, 4) )
                                              * pow( 2.71828182, -( ( x*x + y*y ) /( 2* sigma * sigma ) ));

            Gxy = ( (x * y) / pow(sigma, 4) )
                                              * pow( 2.71828182, -( ( x*x + y*y ) /( 2* sigma * sigma ) ));

            Gtheta[c + (r * kernal_length)] = Gxx * pow(cos(theta), 2) + Gxy * sin(2 * theta) + Gyy * pow(sin(theta), 2);
        }
    }
    return Gtheta;
}

unsigned char* EdgeDetectorSteered(unsigned char* img, int img_height, int img_width,
                                          int kernal_length, double sigma, double theta)
{
    std::vector<double> kernal = kernal_first_order_steered_gaussian(kernal_length,
                                                                    sigma, theta);

    return img_conv(img, img_height, img_width, kernal, kernal_length);
}

unsigned char* ShapeDetectorSteered(unsigned char* img, int img_height, int img_width,
                                          int kernal_length, double sigma, double theta)
{
    std::vector<double> kernal = kernal_second_order_steered_gaussian(kernal_length,
                                                                    sigma, theta);

    return img_conv(img, img_height, img_width, kernal, kernal_length);
}

#endif // LINEAR_FILTERS_H_INCLUDED
