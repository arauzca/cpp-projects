#include <cmath>
#include "oog.h"




Point oog::IFigure::transformToOrigin(const Point &p)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
{
    Point tPoint(p);

    if ( tPoint.y > 0 )
        tPoint.y -= p.y * 2;
    else if ( p.y < 0 )
        tPoint.y += p.y * -2;

    tPoint += origin;

    return tPoint;

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void oog::IFigure::rotate( double angle, const Point & center )
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
{
    double m1[3][3] = { { 1, 0, static_cast<double>(-center.x)},
                        { 0, 1, static_cast<double>(-center.y)},
                        { 0, 0, 1} };
    double m2[3][3] = { { cos(angle), -sin(angle), 0},
                        { sin(angle),  cos(angle), 0},
                        { 0,           0,          1} };
    double m3[3][3] = { { 1, 0, static_cast<double>(center.x)},
                        { 0, 1, static_cast<double>(center.y)},
                        { 0, 0, 1} };

    Mat traslationMatrix( 3, 3, CV_64F, m1);
    Mat rotationMatrix( 3, 3, CV_64F, m2);
    Mat returnMatrix( 3, 3, CV_64F, m3);

    for (auto &point : points) {
        Point p = point;
        double v[3][1] = {{static_cast<double>(p.x)}, {static_cast<double>(p.y)}, {1} };
        Mat vertex(3, 1, CV_64F, v);
        Mat rotatedVertex = returnMatrix * rotationMatrix * traslationMatrix * vertex;
        point = Point(static_cast<int>( round(rotatedVertex.at<double>(0,0)) ),static_cast<int>( round(rotatedVertex.at<double>(1,0)) ));
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




void oog::IFigure::flip( Scalar line)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
{
    Point center(0, static_cast<int>(-line.val[2]));
    double angle = static_cast<double>( atanf(static_cast<float>(-line.val[0] / line.val[1])) );

    double m1[3][3] = { { 1, 0, static_cast<double>(-center.x)},
                        { 0, 1, static_cast<double>(-center.y)},
                        { 0, 0, 1} };
    double m2[3][3] = { { cos(2 * angle),  sin(2 * angle), 0},
                        { sin(2 * angle), -cos(2 * angle), 0},
                        { 0,           0,          1} };
    double m3[3][3] = { { 1, 0, static_cast<double>(center.x)},
                        { 0, 1, static_cast<double>(center.y)},
                        { 0, 0, 1} };

    Mat traslationMatrix( 3, 3, CV_64F, m1);
    Mat rotationMatrix( 3, 3, CV_64F, m2);
    Mat returnMatrix( 3, 3, CV_64F, m3);

    for (auto &point : points) {
        Point p = point;
        double v[3][1] = {{static_cast<double>(p.x)}, {static_cast<double>(p.y)}, {1} };
        Mat vertex(3, 1, CV_64F, v);
        Mat rotatedVertex = returnMatrix * rotationMatrix * traslationMatrix * vertex;
        point = Point(static_cast<int>( round(rotatedVertex.at<double>(0,0)) ),static_cast<int>( round(rotatedVertex.at<double>(1,0)) ));
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




void oog::IFigure::rotate( double angle )
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
{
    rotate( angle, Point(0,0) );
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




oog::Edge::Edge( const Edge & e )
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
{
    start = e.start;
    end = e.end;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




void oog::Edge::getEdge( int & s, int & e )
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
{
    s = start;
    e = end;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




void oog::Face::render( Mat & img )
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
{
    Point face_points[1][points.size()];

    for (unsigned i = 0; i < points.size(); i++ )
    {
        face_points[0][i] = transformToOrigin(points.at(i));
    }

    const Point* ppt[1] = { face_points[0] };
    int npt[] = {static_cast<int>( points.size() ) };

    cv::fillPoly( img,
              ppt,
              npt,
              THICKNESS,
              color,
              LINE_TYPE );
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




void oog::Shape::rotate(double angle, const Point & center)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
{
    double m1[3][3] = { { 1, 0, static_cast<double>(-center.x)},
                        { 0, 1, static_cast<double>(-center.y)},
                        { 0, 0, 1} };
    double m2[3][3] = { { cos(angle), -sin(angle), 0},
                        { sin(angle),  cos(angle), 0},
                        { 0,           0,          1} };
    double m3[3][3] = { { 1, 0, static_cast<double>(center.x)},
                        { 0, 1, static_cast<double>(center.y)},
                        { 0, 0, 1} };

    Mat traslationMatrix( 3, 3, CV_64F, m1);
    Mat rotationMatrix( 3, 3, CV_64F, m2);
    Mat returnMatrix( 3, 3, CV_64F, m3);

    for (auto &face : faces) {
        face.rotate(angle, center);
    }

    for (auto &point : points) {
        Point p = point;
        double v[3][1] = {{static_cast<double>(p.x)},
                          {static_cast<double>(p.y)},
                          {1} };

        Mat vertex(3, 1, CV_64F, v);
        Mat rotatedVertex = returnMatrix * rotationMatrix * traslationMatrix * vertex;
        point = Point(static_cast<int>( round(rotatedVertex.at<double>(0,0)) ), static_cast<int>( round(rotatedVertex.at<double>(1,0)) ));
    }
}




void oog::Shape::flip( Scalar line )
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
{
    Point center(0, static_cast<int>(-line.val[2]));
    auto angle = static_cast<double>( atanf(static_cast<float>(-line.val[0] / line.val[1])) );

    double m1[3][3] = { { 1, 0, static_cast<double>(-center.x)},
                        { 0, 1, static_cast<double>(-center.y)},
                        { 0, 0, 1} };
    double m2[3][3] = { { cos(2 * angle),  sin(2 * angle), 0},
                        { sin(2 * angle), -cos(2 * angle), 0},
                        { 0,           0,          1} };
    double m3[3][3] = { { 1, 0, static_cast<double>(center.x)},
                        { 0, 1, static_cast<double>(center.y)},
                        { 0, 0, 1} };

    Mat traslationMatrix( 3, 3, CV_64F, m1);
    Mat rotationMatrix( 3, 3, CV_64F, m2);
    Mat returnMatrix( 3, 3, CV_64F, m3);

    for (auto &face : faces) {
        face.flip( line );
    }

    for (auto &point : points) {
        Point p = point;
        double v[3][1] = {{static_cast<double>(p.x)}, {static_cast<double>(p.y)}, {1} };
        Mat vertex(3, 1, CV_64F, v);
        Mat rotatedVertex = returnMatrix * rotationMatrix * traslationMatrix * vertex;
        point = Point(static_cast<int>( round(rotatedVertex.at<double>(0,0)) ),static_cast<int>( round(rotatedVertex.at<double>(1,0)) ));
    }

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




void oog::Shape::render( Mat & img )
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
{
    if (edges.empty()) edges.emplace_back(0,0);

    for (auto &face : faces) {
        face.render( img );
    }

    for (auto e : edges) {
        int p1(0), p2(0);
        e.getEdge( p1, p2 );
        Point start(transformToOrigin(points.at( static_cast<unsigned long>(p1) )));
        Point end(transformToOrigin(points.at(static_cast<unsigned  long>(p2) )));

        line ( img,
               start,
               end,
               Scalar( 0, 0, 0 ),
               THICKNESS,
               LINE_TYPE );
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




void oog::Shape::rotate( double angle )
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
{
    rotate( angle, Point(0,0) );
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




void oog::InitWindows( Mat & img )
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
{
    // Filling background
    rectangle( img,
               Point( 0, 0 ),
               Point( _WINDOWS_WIDTH_, _WINDOWS_WIDTH_),
               Scalar( 255, 255, 255 ),
               -1,
               LINE_TYPE );

    line( img,
          Point( _WINDOWS_WIDTH_ / 2, 0 ),
          Point( _WINDOWS_WIDTH_ / 2, _WINDOWS_WIDTH_ ),
          Scalar( 0, 0, 0 ),
          THICKNESS,
          LINE_TYPE );

    line( img,
          Point( 0,               _WINDOWS_WIDTH_ / 2),
          Point( _WINDOWS_WIDTH_, _WINDOWS_WIDTH_ / 2),
          Scalar( 0, 0, 0 ),
          THICKNESS,
          LINE_TYPE );


}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
