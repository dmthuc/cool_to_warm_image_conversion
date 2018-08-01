#ifndef __DEFINES_HPP
#define __DEFINES_HPP
#include <opencv2/opencv.hpp>
#include <opencv2/core/cvdef.h>

/*
    Pixel.z is Red channel
    Pixel.x is Blue channel
    Pixel.y is Green channel
*/
using Pixel = cv::Point3_<uint8_t> ;
constexpr double PI = CV_PI;
constexpr double PIdiv2 = PI/2;
constexpr double PIdiv3 = PI/3;
constexpr double PIdiv4 = PI/4;
#endif

