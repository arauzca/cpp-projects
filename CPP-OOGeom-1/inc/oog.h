/*/////////////////////////////////////////////////////////////////////////////
module:  object oriented geometry
purpose: implements operations for transformation of figures in 2-dimensional space

written:  Carlos Arauz
initials: arauc1

/////////////////////////////////////////////////////////////////////////////*/
#pragma once

// OpenCV includes /////////////////////////////////////////////////////////////////////////////////////////////////////
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;




// system includes /////////////////////////////////////////////////////////////////////////////////////////////////////
#include <vector>
#include <iostream>




// macro definitions ///////////////////////////////////////////////////////////////////////////////////////////////////
#define _WINDOWS_WIDTH_ 720




namespace oog {
    static const int THICKNESS = 1;
    static const int LINE_TYPE = 8;


    class IFigure {
    public:
        std::vector<Point> points;
    protected:
        Point origin;
    public:
        IFigure() = default;

        explicit IFigure( const Point  & o) : origin( o) {};

        virtual void render(Mat &) = 0;

        virtual void rotate(double);

        virtual void rotate(double, const Point &);

        virtual void flip(Scalar);

    protected:
        Point transformToOrigin(const Point &);
    };


    class Edge {
    private:
        int start = 0;
        int end   = 0;
        Scalar color;
    public:
        Edge() = default;

        /**
         *
         * @param s Start point of the edge
         * @param e End point of the edge
         */
        Edge(const int &s, const int &e) : Edge(s, e, Scalar(0, 0, 0)) {};

        Edge(const int &s, const int &e, Scalar c) : start(s), end(e), color(std::move(c)) {};

        Edge(const Edge &);

        Edge(Edge &&other) noexcept : start( other.start ), end( other.end ), color( std::move(other.color) ) {};

        Edge &operator=(const Edge &other) = default;

        void getEdge(int &, int &);
    };


    class Face : public IFigure {
    private:
        Scalar color;
    public:
        Face(const Point &o, Scalar c) : IFigure(o), color( std::move(c) ) {};

        void render(Mat &) override;
    };


    class Shape : public IFigure {
    public:
        std::vector<Edge> edges;
        std::vector<Face> faces;
    public:
        Shape(double center_x, double center_y) { origin = Point(static_cast<int>(center_x), static_cast<int>(center_y)); };

        explicit Shape(const Point &o) : IFigure(o) {};

        void render(Mat &img) override;

        void rotate(double) override;

        void rotate(double, const Point &) override;

        void flip(Scalar) override;
    };

    void InitWindows(Mat &img);

}