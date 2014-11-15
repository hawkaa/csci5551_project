#include <math.h>
#include "geometry.h"
Point::Point(double x, double y)
{
  this->x = x;
  this->y = y;
}

double
Point::getX(void)
{
  return this->x;
}

double
Point::getY(void)
{
  return this->y;
}

LineSegment::LineSegment(Point *start, Point *stop)
{
  this->start = start;
  this->stop = stop;
}

double
LineSegment::getLength(void)
{
  return sqrt(pow(this->start->getX(), 2) + pow(this->stop->getY(), 2));
}

Point *
LineSegment::getCenter(void)
{
  double x = (start->getX() + stop->getX()) / 2.0;
  double y = (start->getY() + stop->getY()) / 2.0;
  return new Point(x, y);
}
