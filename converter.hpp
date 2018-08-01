#ifndef __CONVERT_HPP
#define __CONVERT_HPP
#include <iostream>
#include <cmath>
#include <opencv2/opencv.hpp>
#include "pixel_helper.hpp"


namespace ORGB
{
    struct Point2D{
        double x;
        double y;
    };

    struct Shift_val {
        double red;
        double yellow; 
    };

    inline bool operator==(const Point2D lhs, const Point2D rhs)
    {
        return (lhs.x == rhs.x) && (lhs.y == rhs.y);
    }


    Point2D round(const Point2D point);
    cv::Mat mean_shift(const cv::Mat& in, Shift_val shift_val);
    LCC_point RGB_to_LCC(const RGB_point& rgb);
    RGB_point LCC_to_RGB(const LCC_point& lcc);
    ORGB_point LCC_to_ORGB(const LCC_point& lcc);
    LCC_point ORGB_to_LCC(const ORGB_point& orgb);
    Point2D rotate(double angle, const Point2D origin);

    std::ostream& operator<<(std::ostream& os, const Point2D p);
}
#endif
