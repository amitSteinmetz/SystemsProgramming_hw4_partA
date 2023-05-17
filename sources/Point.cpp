#include "Point.hpp"

// Ctors
    Point::Point(double x, double y) : x(x), y(y)
    {}

    // Methods
    double Point::distance(const Point other) const
    {
        return 1;
    }
    void Point::print() const
    {
        return;
    }
    Point Point::moveTowards(Point src, Point dst, double distance)
    {
        return Point(0,0);
    }
    double Point::getX() const
    {
        return x;
    }
    void Point::setX(double new_x)
    {
        x = new_x;
    }
    double Point::getY() const
    {
        return y;
    }
    void Point::setY(double new_y)
    {
        y = new_y;
    }