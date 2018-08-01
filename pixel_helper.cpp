#include <iostream>
#include "pixel_helper.hpp"
using std::cout;
using std::endl;
using std::ostream;

namespace ORGB
{

RGB_point to_RGB_point(const Pixel pixel) 
{
    assert((pixel.x <= 255) && (pixel.y <= 255) && (pixel.z <= 255)
            && (pixel.x >= 0) && (pixel.y >= 0) && (pixel.z >= 0));
    RGB_point p;
    p.r = static_cast<double>(pixel.z)/255;
    p.g = static_cast<double>(pixel.y)/255;
    p.b = static_cast<double>(pixel.x)/255;
    return p;
    //return RGB_point{static_cast<double>(pixel.z/255), static_cast<double>(pixel.y/255, pixel.x/255};
}


/*
    Pixel.z is Red channel
    Pixel.x is Blue channel
    Pixel.y is Green channel
*/
Pixel to_Pixel(const RGB_point& rgb)
{
    assert( (rgb.r <= 1) && (rgb.r >= 0) &&
            (rgb.b <= 1) && (rgb.b >= 0) &&
            (rgb.g <= 1) && (rgb.g >= 0) );
    Pixel p;
    p.x = round(rgb.b* 255);
    p.y = round(rgb.g* 255);
    p.z = round(rgb.r* 255);
    return p;
}

ostream& operator<<(ostream& os, const Pixel p)
{
    os<<(int)p.x<<'\t'<<(int)p.y<<'\t'<<(int)p.z;
    return os;
}

ostream& operator<<(ostream& os, const RGB_point p)
{
    os<<p.r<<'\t'<<p.g<<'\t'<<p.b;
    return os;
}

ostream& operator<<(ostream& os, const LCC_point p)
{
    os<<p.l<<'\t'<<p.c1<<'\t'<<p.c2;
    return os;
}

double clamp_to_absolute_val(double val, const int ref)
{
    assert( ref>= 0);
    if (val > ref)
        return ref;
    else if (val < -ref)
        return -ref;
    return val;
}


LCC_point& LCC_point::clamp() {
    if (l <0)
        l = 0;
    else if (l > 1)
        l = 1;
    c1 = clamp_to_absolute_val(c1, 1);
    c2 = clamp_to_absolute_val(c2, 1);
    return *this;
}

RGB_point& RGB_point::clamp() {
    auto clamp = [] (double& d) {
        if (d < 0)
            d = 0;
        else if (d > 1)
            d = 1;
    };
    clamp(r);
    clamp(g);
    clamp(b);
    return *this;
}

}

