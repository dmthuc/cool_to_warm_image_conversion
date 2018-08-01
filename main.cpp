#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "defines.hpp"
#include "converter.hpp"
using std::cout;
using std::endl;
using cv::Mat;
using cv::resize;
using cv::IMREAD_COLOR;
using cv::imread;
using cv::WINDOW_AUTOSIZE;
using cv::namedWindow;
using cv::waitKey;
using ORGB::mean_shift;
using ORGB::Shift_val;

Mat demo_warm_to_cool(const Mat& in)
{
    Mat composed(in.rows *3, in.cols*3, in.type());

    Mat left_up = mean_shift(in, Shift_val{0.2,-0.2});
    Mat roi = composed(cv::Rect(0,0,in.cols,in.rows));
    left_up.copyTo(roi);

    Mat up = mean_shift(in, Shift_val{0.2,0.0});
    roi = composed(cv::Rect(in.cols,0,in.cols,in.rows));
    up.copyTo(roi);

    Mat right_up = mean_shift(in, Shift_val{0.2,0.2});
    roi = composed(cv::Rect(in.cols*2,0,in.cols,in.rows));
    right_up.copyTo(roi);

    Mat left = mean_shift(in, Shift_val{0.0,-0.2});
    roi = composed(cv::Rect(0,in.rows,in.cols,in.rows));
    left.copyTo(roi);

    Mat right = mean_shift(in, Shift_val{0.0,0.2});
    roi = composed(cv::Rect(in.cols*2,in.rows,in.cols,in.rows));
    right.copyTo(roi);

    Mat left_down = mean_shift(in, Shift_val{-0.2,-0.2});
    roi = composed(cv::Rect(0,in.rows*2,in.cols,in.rows));
    left_down.copyTo(roi);

    Mat down = mean_shift(in, Shift_val{-0.2,0.0});
    roi = composed(cv::Rect(in.cols,in.rows*2,in.cols,in.rows));
    down.copyTo(roi);

    Mat right_down = mean_shift(in, Shift_val{-0.2,0.2});
    roi = composed(cv::Rect(in.cols*2,in.rows*2,in.cols,in.rows));
    right_down.copyTo(roi);
    
    roi = composed(cv::Rect(in.cols,in.rows,in.cols,in.rows));
    in.copyTo(roi);
    constexpr double Scale_factor = 0.5;
    Mat scale_composed;
    resize(composed, scale_composed, cvSize(0, 0), Scale_factor, Scale_factor);
    return scale_composed;
}


int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }

    Mat original_image;
    /* this method read the image, decoded channels stored in B R G  
       with numer of channel is 3, dimension is 2 , dept is 0 (CV_8U) range from 0 .. 255 
    */
    original_image = imread(argv[1], IMREAD_COLOR);

    if (!original_image.data )
    {
        printf("No image data \n");
        return -1;
    }
    assert(original_image.depth() == CV_8U);
    Mat res = demo_warm_to_cool(original_image);
    
    namedWindow("Original Image", WINDOW_AUTOSIZE );
    imshow("Original Image", original_image);

    namedWindow("Result Image", WINDOW_AUTOSIZE );

    imshow("Result Image", res);
    //imwrite("result.png", res);

    waitKey(0);

    return 0;
}

