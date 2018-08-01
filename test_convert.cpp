#include <iostream>
#include "pixel_helper.hpp"
#include "converter.hpp"

using std::cout;
using std::endl;
using namespace ORGB;

int main()
{
    {
        Pixel p;
        p.x = p.y = p.z = 10;
        auto rgb = to_RGB_point(p);
        //cout<<rgb<<endl;
        auto lcc = RGB_to_LCC(rgb);
        //cout<<lcc<<endl;
        rgb = LCC_to_RGB(lcc);
        //cout<<rgb<<endl;
        auto ip = to_Pixel(rgb);
        //cout<<ip<<endl;
        assert(p == ip);
    }

    {
        Pixel p;
        p.x = p.y = p.z = 10;
        auto rgb = to_RGB_point(p);
        auto lcc = RGB_to_LCC(rgb);
        auto orgb = LCC_to_ORGB(lcc);
        lcc = ORGB_to_LCC(orgb);
        rgb = LCC_to_RGB(lcc);
        auto ip = to_Pixel(rgb);
        assert(p == ip);
    }
    {
        Point2D origin{0.745098,0};
        Point2D res =  rotate(0, origin);
        assert(round(origin) == round(res));
    }
    {
        Point2D origin{0.745098,1};
        Point2D res =  rotate(1, origin);
        Point2D iorigin = rotate(-1, res);
        assert(round(origin) == round(iorigin));
    }
    {
        Pixel p;
        p.x = 10;
        p.y = p.z = 200;
        auto rgb = to_RGB_point(p);
        auto lcc = RGB_to_LCC(rgb);
        auto orgb = LCC_to_ORGB(lcc);
        lcc = ORGB_to_LCC(orgb);
        rgb = LCC_to_RGB(lcc);
        auto ip = to_Pixel(rgb);
        assert(p == ip);
    }
    {
        Pixel p;
        p.x = 10;
        p.y = 200;
        p.z = 255;
        auto rgb = to_RGB_point(p);
        auto lcc = RGB_to_LCC(rgb);
        auto orgb = LCC_to_ORGB(lcc);
        lcc = ORGB_to_LCC(orgb);
        rgb = LCC_to_RGB(lcc);
        auto ip = to_Pixel(rgb);
        assert(p == ip);
    }
}

