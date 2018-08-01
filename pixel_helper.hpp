#ifndef __PIXEL_HELPER_HPP
#define __PIXEL_HELPER_HPP
#include <iostream>
#include "defines.hpp"

namespace ORGB
{
    struct LCC_point
    {
        double l;
        double c1;//blue-yellow
        double c2;//green-red
        LCC_point& clamp(); 
    };

    using ORGB_point = LCC_point;

    struct RGB_point
    {
        double r;
        double g;
        double b;
        RGB_point& clamp(); 
    };

    /*
        Pixel.z is Red channel
        Pixel.x is Blue channel
        Pixel.y is Green channel
    */
    RGB_point to_RGB_point(const Pixel pixel);
    Pixel to_Pixel(const RGB_point& point);
    std::ostream& operator<<(std::ostream& os, const Pixel p);
    std::ostream& operator<<(std::ostream& os, const RGB_point p);
    std::ostream& operator<<(std::ostream& os, const LCC_point p);
} 
#endif

