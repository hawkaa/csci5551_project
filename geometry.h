#pragma once

class Point {
  private:
    double x, y;
  public:
    Point(double, double);
    double getX(void);
    double getY(void);
};

class LineSegment {
  private:
    Point *start, *stop;
  public:
    LineSegment(Point*, Point*);
    double getLength(void);
    Point *getCenter(void);
};
