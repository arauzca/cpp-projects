#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <cmath>
#include "oog.h"

#define SIDE_SIZE 75

using namespace cv;
oog::Shape drawFigure( Mat & img );

/**
 * @function main
 * @brief Main function
 */
int main(){

    //![create_images]
    /// Windows names
    char shape_window[] = "Shape";

    /// Create black empty images
    Mat shape_image = Mat::zeros( _WINDOWS_WIDTH_, _WINDOWS_WIDTH_, CV_8UC3 );

    /// Draw cartesian plane
    oog::InitWindows( shape_image );
    //![create_images]

    /// Draw the figure
    oog::Shape p = drawFigure( shape_image );
    p.flip( Scalar(1,1,0) );
    p.render( shape_image );

    /// 3. Display your stuff!
    imshow( shape_window, shape_image );
    moveWindow( shape_window, 200, 200 );

    waitKey( 0 );
    return(0);
}

/**
 * @brief Draw the square in the exercise
 * @param img base image
 */
oog::Shape drawFigure( Mat & img )
{
    oog::Shape p = oog::Shape( Point( _WINDOWS_WIDTH_ / 2, _WINDOWS_WIDTH_ / 2 ) );
    p.points.emplace_back(SIDE_SIZE,     SIDE_SIZE);                      // Point: 0
    p.points.emplace_back(SIDE_SIZE,     SIDE_SIZE * 2);                  // Point: 1
    p.points.emplace_back(SIDE_SIZE,     SIDE_SIZE * 3);                  // Point: 2
    p.points.emplace_back(SIDE_SIZE * 2, SIDE_SIZE);                      // Point: 3
    p.points.emplace_back(SIDE_SIZE * 2, SIDE_SIZE * 3);                  // Point: 4
    p.points.emplace_back(SIDE_SIZE * 3, SIDE_SIZE);                      // Point: 5
    p.points.emplace_back(SIDE_SIZE * 3, SIDE_SIZE * 2);                  // Point: 6
    p.points.emplace_back(SIDE_SIZE * 3, SIDE_SIZE * 3);                  // Point: 7

    p.edges.emplace_back(0,2);
    p.edges.emplace_back(2,7);
    p.edges.emplace_back(5,7);
    p.edges.emplace_back(0,5);
    p.edges.emplace_back(3,4);
    p.edges.emplace_back(1,6);

    oog::Face f( Point( _WINDOWS_WIDTH_ / 2, _WINDOWS_WIDTH_ / 2 ), Scalar( 0, 0, 255 ) );
    f.points.emplace_back(p.points.at(3));
    f.points.emplace_back(SIDE_SIZE * 2, SIDE_SIZE * 2);
    f.points.emplace_back(p.points.at(6));
    f.points.emplace_back(p.points.at(5));

    p.faces.push_back(f);

    p.render( img );
    return p;
}