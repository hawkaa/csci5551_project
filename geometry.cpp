#include <math.h>
#include <cstdio>
#include <iostream>
#include "geometry.h"

Point::Point(){}

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

double
Point::distanceTo(Point *p)
{
  LineSegment ls = LineSegment(this, p);
  return ls.getLength();
}

LineSegment::LineSegment(Point *start, Point *stop)
{
  this->start = start;
  this->stop = stop;
}

Point *
LineSegment::getStart(void)
{
  return this->start;
}

Point *
LineSegment::getStop(void)
{
  return this->stop;

}
double
LineSegment::getLength(void)
{
  return sqrt(pow(this->start->getX()-this->stop->getX(), 2) + pow(this->start->getY()-this->stop->getY(), 2));
}

Point 
LineSegment::getCenter(void)
{
  double x = (start->getX() + stop->getX()) / 2.0;
  double y = (start->getY() + stop->getY()) / 2.0;
  return Point(x, y);
}

std::vector<LineSegment> *
Geometry::getLineSegments(std::vector<Point> *points, double threshold)
{
  double distance;
  std::vector<LineSegment> *lineSegments = new std::vector<LineSegment>();

  Point *startCandidate = &points->at(0);
  Point *stopCandidate = &points->at(0);
  
  for (int i = 0; i < points->size(); ++i) {
    distance = stopCandidate->distanceTo(&points->at(i));
    if (distance >= threshold) {
      /* save the line segment if it's not 0 */
      if (startCandidate != stopCandidate) {
        lineSegments->push_back(LineSegment(startCandidate, stopCandidate));  
      }
      startCandidate = &points->at(i); 
    }  
    stopCandidate = &points->at(i);
  }

  if (startCandidate != stopCandidate) {
    lineSegments->push_back(LineSegment(startCandidate, stopCandidate));  
  }
  return lineSegments;

}

void 
Geometry::filterByLength(std::vector<LineSegment> *lineSegments, double min, double max)
{
  double length;
  
  int i = 0;
  
  while (i < lineSegments->size()) {
    length = lineSegments->at(i).getLength();
    if (length <= min || length >= max) {
      lineSegments->erase(lineSegments->begin() + i); 
    } else {
      ++i;
    }
  }
}

std::vector<Point> *
Geometry::getCentroids(std::vector<LineSegment> *lineSegments)
{
  std::vector<Point> *centroids = new std::vector<Point>();
  for (int i = 0; i < lineSegments->size(); ++i) {
    centroids->push_back(lineSegments->at(i).getCenter());
  }
  return centroids;
}

std::vector<LineSegment> *
Geometry::getLegs(std::vector<Point> *centroids, double min, double max)
{ 
  double distance;
  std::vector<LineSegment> *legs = new std::vector<LineSegment>();
  for (int i = 0; i < centroids->size(); ++i) {
    for(int j = i + 1; j < centroids->size(); ++j) {
      distance = centroids->at(i).distanceTo(&centroids->at(j));
      if (distance >= min && distance <= max) {
        legs->push_back(LineSegment(&centroids->at(i), &centroids->at(j)));
        ++i; ++j;
      }
    }
  }

  return legs;
}

void
Geometry::dumpPoints(std::vector<Point> *points, FILE *fh)
{
  for (int i = 0; i < points->size(); ++i) {
    printf("%f %f\n", points->at(i).getX(), points->at(i).getY()); 
    if (fh != NULL)
      fprintf(fh, "%f %f\n", points->at(i).getX(), points->at(i).getY()); 
  }
}

void
Geometry::dumpLineSegments(std::vector<LineSegment> *lineSegments, FILE *fh)
{
  for (int i = 0; i < lineSegments->size(); ++i) {
    printf("Start: %f %f \t Stop: %f %f, Length: %f\n", 
      lineSegments->at(i).getStart()->getX(),
      lineSegments->at(i).getStart()->getY(),
      lineSegments->at(i).getStop()->getX(),
      lineSegments->at(i).getStop()->getY(),
      lineSegments->at(i).getLength()
    );
    if (fh != NULL) {
      fprintf(fh, "%f %f\n", lineSegments->at(i).getStart()->getX(), lineSegments->at(i).getStart()->getY()); 
      fprintf(fh, "%f %f\n", lineSegments->at(i).getStop()->getX(), lineSegments->at(i).getStop()->getY()); 
      fprintf(fh, "\n");
    }
  }

}

std::vector<Point> *
Geometry::getPointsFromFile(char *filename)
{
  char line[80];
  double x, y;
  std::vector<Point> *readings = new std::vector<Point>();
  FILE *fh = fopen(filename, "r");
  while (fgets(line, 80, fh) != NULL) {
    sscanf(line, "%lf %lf\n", &x, &y);
    Point p = Point(x, y);
    readings->push_back(p);
  }
  fclose(fh);
  return readings;
}

Point *
Geometry::getClosest(std::vector<LineSegment> *lineSegments, Point *origin)
{
  double distance = 0.0;
  Point *closest = NULL;
  Point center;
  for (int i = 0; i < lineSegments->size(); ++i) {
    center = lineSegments->at(i).getCenter();
    if (closest == NULL) {
      distance = center.distanceTo(origin);
      closest = new Point(center.getX(), center.getY());
    } else {
      if (center.distanceTo(origin) < distance) {
        distance = center.distanceTo(origin);
        delete closest;
        closest = new Point(center.getX(), center.getY());
      }
    }
  }
  return closest;

}
