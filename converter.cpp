#include <iostream>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <array>
#include "pixel_helper.hpp"
#include "converter.hpp"


using std::cout;
using std::ostream;
using std::round;
using std::endl;
using std::runtime_error;
using cv::Mat;

namespace ORGB
{

Point2D rotate(double angle, const Point2D origin);
LCC_point RGB_to_LCC(const RGB_point& rgb);
RGB_point LCC_to_RGB(const LCC_point& lcc);
ORGB_point LCC_to_ORGB(const LCC_point& lcc);
LCC_point ORGB_to_LCC(const ORGB_point& orgb);

Point2D round(const Point2D p)
{
    double x = std::round((p.x*255))/255;
    double y = std::round((p.y*255))/255;
    return Point2D{x,y};
}


ORGB_point mean_shift(const ORGB_point &p, Shift_val shift_val)
{
    ORGB_point ret{p.l,p.c1 + shift_val.yellow,p.c2 + shift_val.red};
    return ret.clamp();
}

#if 0
//shift_to_yellow(orgb_point,-0.3);
void shift_to_yellow(ORGB_point &p, double val)
{
    p.c1 += val;
    clam_to_absolute_val(p.c1,1);
}

void shift_to_red(ORGB_point &p, double val)
{
    p.c2 += val;
    clam_to_absolute_val(p.c2,1);
}
#endif
Mat mean_shift(const Mat& in, Shift_val shift_val)
{
    Mat result = in.clone();

    result.forEach<Pixel>([shift_val](Pixel &p, const int * ) -> void {
        auto rgb_point = to_RGB_point(p);
        auto lcc_point = RGB_to_LCC(rgb_point);
        auto orgb_point = LCC_to_ORGB(lcc_point);
        orgb_point = mean_shift(orgb_point, shift_val);
        auto inverted_lcc_point = ORGB_to_LCC(orgb_point);
        auto inverted_rgb_point = LCC_to_RGB(inverted_lcc_point);
        auto inverted_pixel = to_Pixel(inverted_rgb_point); 
        p = inverted_pixel;
    });
    
    return result;
}


Point2D rotate(double angle, const Point2D origin)
{
    Point2D res; 

    double cos = std::cos(angle);
    double sin = std::sin(angle);

    res.x = (origin.x * cos) - (origin.y * sin);
    res.y = (origin.x * sin) + (origin.y * cos);
    return res;
}


LCC_point RGB_to_LCC(const RGB_point& rgb)
{
    LCC_point lcc;
    lcc.l  = 0.299 * rgb.r + 0.5870*rgb.g + 0.1140 * rgb.b;
    lcc.c1 = 0.5   * rgb.r + 0.5   *rgb.g - 1      * rgb.b;
    lcc.c2 = 0.866 * rgb.r - 0.866 *rgb.g;// +0.0* rgb[2];

    return lcc;
}


RGB_point LCC_to_RGB(const LCC_point& lcc)
{
    assert( (lcc.l >= 0) && (lcc.l <=1) &&
            (lcc.c1 >= -1) && (lcc.c1 <=1) &&
            (lcc.c2 >= -1) && (lcc.c2 <=1) );
    RGB_point rgb;
    rgb.r = 1*lcc.l + 0.114*lcc.c1 + 0.7436*lcc.c2;
    rgb.g = 1*lcc.l + 0.114*lcc.c1 - 0.4111*lcc.c2;
    rgb.b = 1*lcc.l - 0.886*lcc.c1 + 0.1663*lcc.c2;
    rgb.clamp();
    assert((rgb.r >=0) && (rgb.r <=1) &&
           (rgb.g >=0) && (rgb.g <=1) &&
           (rgb.b >=0) && (rgb.b <=1) ); 
    return rgb;
}

ORGB_point LCC_to_ORGB(const LCC_point& lcc)
{
    ORGB_point orgb;
    orgb.l = lcc.l;  
    if ((lcc.c2 == 0) && (lcc.c1 == 0)) {
        orgb.c1 = orgb.c2 = 0;
        return orgb;
    }

    double angle = atan2(lcc.c2, lcc.c1);
    auto get_new_angle = [] (double angle) -> double {
        assert((angle >= -PI) && (angle <= PI));
        if ((angle < PIdiv3) && (angle > -PIdiv3))
            return angle*1.5;
        else if ((angle <=  PI) && (angle >=  PIdiv3))
            return (3.0/4) * angle + PIdiv4;
        else if ((angle >= -PI) && (angle <= -PIdiv3))
            return (3.0/4) * angle - PIdiv4;
        else
            throw runtime_error("invalid angle");
    };

    double new_angle = get_new_angle(angle);
    const Point2D rotated_point = rotate((new_angle-angle) , Point2D{lcc.c1,lcc.c2});
    orgb.c1 = rotated_point.x;
    orgb.c2 = rotated_point.y;

    assert( (orgb.l >= 0) && (orgb.l <=1) &&
            (orgb.c1 >= -1) && (orgb.c1 <=1) &&
            (orgb.c2 >= -1) && (orgb.c2 <=1) );
    return orgb;
}


LCC_point ORGB_to_LCC(const ORGB_point& orgb)
{
    LCC_point lcc;
    //assert((orgb.l <= 1) && (orgb.c1 <=1) && (orgb.c2 <=1));
    lcc.l = orgb.l;

    if ((orgb.c2 == 0) && (orgb.c1 == 0)) {
        lcc.c1 = lcc.c2 = 0;
        return lcc;
    }
    double angle = atan2(orgb.c2, orgb.c1);
    auto get_new_angle = [] (double angle) -> double {
        assert((angle >= -PI) && (angle <= PI));
        if ((angle > -PIdiv2) && (angle < PIdiv2)) {
            return angle* (2.0/3);
        }
        else if ((angle <=  PI) && (angle >= PIdiv2))
        {
            return (4.0/3) * angle - PIdiv3;
        }
        else if ((angle >= -PI) && (angle <= -PIdiv2))
        {
            return (4.0/3) * angle + PIdiv3;
        }
        else
            throw runtime_error("invalid angle");
    };

    double new_angle = get_new_angle(angle);
    const Point2D rotated_point = rotate((new_angle-angle) , Point2D{orgb.c1, orgb.c2});
    lcc.c1 = rotated_point.x;
    lcc.c2 = rotated_point.y;

    lcc.clamp();;
    assert( (lcc.l >= 0) && (lcc.l <=1) &&
            (lcc.c1 >= -1) && (lcc.c1 <=1) &&
            (lcc.c2 >= -1) && (lcc.c2 <=1) );
    return lcc;
}


ostream& operator<<(ostream& os, const Point2D p)
{
    os <<"p.x:"<<p.x<<"\tp.y:"<<p.y;
    return os;
}

}

