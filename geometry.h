#pragma once

#include <vector>

class Point {
  private:
    double x, y;
  public:
    Point(double, double);
    double getX(void);
    double getY(void);
    double distanceTo(Point *p);
};

class LineSegment {
  private:
    Point *start, *stop;
  public:
    LineSegment(Point*, Point*);
    double getLength(void);
    Point *getCenter(void);
    Point *getStart(void);
    Point *getStop(void);
};

class Geometry {
  public:
    static std::vector<LineSegment> * getLineSegments(std::vector<Point> *points);
    static std::vector<Point> * getPointsFromFile(char *filename);
    static void dumpPoints(std::vector<Point> *points);
    static void dumpLineSegments(std::vector<LineSegment> *lineSegments);
};
