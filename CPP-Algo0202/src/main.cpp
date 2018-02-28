#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <unistd.h>

using namespace cv;

void floodFillAlgo(Mat &, int, int);

int main()
{
    Mat image = Mat::ones(256, 256, CV_64F);
    image.at<double>(124,128) = 0;
    image.at<double>(131,128) = 0;
    
    image.at<double>(125,129) = 0;
    image.at<double>(126,130) = 0;
    image.at<double>(127,131) = 0;
    image.at<double>(128,132) = 0;
    image.at<double>(129,132) = 0;
    image.at<double>(130,132) = 0;
    image.at<double>(131,131) = 0;
    image.at<double>(132,130) = 0;
    image.at<double>(132,129) = 0;
    
    image.at<double>(125,127) = 0;
    image.at<double>(126,126) = 0;
    image.at<double>(127,125) = 0;
    image.at<double>(128,124) = 0;
    image.at<double>(129,124) = 0;
    image.at<double>(130,124) = 0;
    image.at<double>(131,125) = 0;
    image.at<double>(132,126) = 0;
    image.at<double>(132,127) = 0;
    
    rotate(image, image, ROTATE_180);
    
    imshow("Heart", image);
    
    floodFillAlgo(image, 128, 128);
    
    imshow("Filled Heart", image);
    
    waitKey();
    return 0;
}

void floodFillAlgo(Mat & im, int col, int row)
{
    if (col >= 0 && row >= 0 && col < im.cols && row < im.rows && im.at<double>(row,col) != 0)
    {
        im.at<double>(row,col) = 0;
        
        floodFillAlgo(im, col + 1, row);
        floodFillAlgo(im, col - 1, row);
        floodFillAlgo(im, col,     row + 1);
        floodFillAlgo(im, col,     row - 1);
        
    }
}
