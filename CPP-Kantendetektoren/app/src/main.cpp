#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;

namespace CPVR {
    void addGaussianNoise(const Mat &src, Mat &dst, double percent)
    {
        Mat imGray;
        cvtColor(src,imGray,CV_BGR2GRAY);
        cv::Mat noise = Mat(src.size(), CV_32F);

        normalize(imGray, dst, 0.0, 1.0, CV_MINMAX, CV_32F);
        cv::randn(noise, 0.0, percent);
        dst = dst + noise;
        normalize(dst, dst, 0.0, 1.0, CV_MINMAX, CV_32F);
    }

    void applySobelFilter(const Mat &src, Mat &dst)
    {
        Mat src_gray;
        int scale = 1;
        int delta = 0;
        int ddepth = CV_16S;

        //GaussianBlur( src, src, Size(3,3), 0, 0, BORDER_DEFAULT );

        /// Convert it to gray
        cvtColor( src, src_gray, CV_GRAY2BGR );
        cvtColor( src_gray, src_gray, CV_BGR2GRAY );

        /// Generate grad_x and grad_y
        Mat grad_x, grad_y;
        Mat abs_grad_x, abs_grad_y;

        /// Gradient X
        //Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
        Sobel( src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
        convertScaleAbs( grad_x, abs_grad_x );

        /// Gradient Y
        //Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
        Sobel( src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
        convertScaleAbs( grad_y, abs_grad_y );

        /// Total Gradient (approximate)
        addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst );

    }

    void applyBinaryFilter(const Mat &src, Mat &dst, double thresh)
    {
        threshold(src, dst, thresh, 255, THRESH_BINARY);
    }
}

int main ( int argc, char** argv )
{
    Mat input = imread("cameraman.tif");
    Mat input_noise_1;
    Mat input_noise_5;
    Mat input_sobel;

    CPVR::addGaussianNoise(input, input_noise_1, 0.01);
    CPVR::addGaussianNoise(input, input_noise_5, 0.05);

    //CPVR::applySobelFilter(input, input_sobel);

    imshow( "Original image", input );
    imshow( "Gaussian noise 1%", input_noise_1 );
    imshow( "Gaussian noise 5%", input_noise_5 );
    //imshow( "Sobel", input_sobel);

    //CPVR::applyBinaryFilter(input_sobel, input_sobel, 255 / 2);
    //imshow( "Sobel Binary", input_sobel);

    waitKey();
    return 0;
}