#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <unistd.h>

using namespace cv;

const int UNITS = 5;                        // default: 5
const int SPACE_BETWEEN_LINES = 6;          // default: 6
const int SMALLEST_LINE_SIZE = 10;          // default: 5
const int WINDOW_SIZE = 256;                // default: 256

int x_init = SMALLEST_LINE_SIZE;
int y_init = WINDOW_SIZE/2 + SMALLEST_LINE_SIZE*UNITS/2;

void floodFillAlgo(Mat &, int, int);
void rulerAlgo(Mat &, int);
void drawLine(Mat &, int);

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
    
    Mat im_gray = imread("/Users/arauzca/Downloads/lena-binary.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    Mat im_bin   = im_gray > 128;
    im_bin.convertTo(im_bin, CV_64F);
    imshow("Lena Binary", im_bin);
    
    floodFillAlgo(im_bin, 150, 110);
    imshow("Filled Lena", im_bin);
    
    int col_size = (SPACE_BETWEEN_LINES*pow(2.0, UNITS)) + SMALLEST_LINE_SIZE;
    Mat im_ruler = Mat::ones(WINDOW_SIZE, col_size, CV_64F);
    rulerAlgo(im_ruler, UNITS);
    imshow("Ruler", im_ruler);
    
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

void rulerAlgo(Mat & im, int n)
{
    if (n == 1) drawLine(im, 1);
    else
    {
        rulerAlgo(im, n - 1);
        drawLine(im, n);
        rulerAlgo(im, n - 1);
    }
}

void drawLine(Mat & im, int k)
{
    int y_aux = y_init;
    
    for(int i = 0; i < k; i++)
    {
        for(int j = 0; j < SMALLEST_LINE_SIZE; j++)
        {
            im.at<double>(y_aux--,x_init) = 0;
        }
    }
    
    x_init += SPACE_BETWEEN_LINES;  // increase x_init
}
