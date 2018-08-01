#include <iostream>
#include "pixel_helper.hpp"

using std::cout;
using std::endl;
using namespace ORGB;

int main()
{
    Pixel p;
    p.x = p.y = p.z = 10;
    auto rgb = to_RGB_point(p);
    auto i_pixel = to_Pixel(rgb);
    assert(p == i_pixel);
}

