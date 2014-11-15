#include <math.h>
#include <cstdio>
#include <iostream>
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

Point *
LineSegment::getCenter(void)
{
  double x = (start->getX() + stop->getX()) / 2.0;
  double y = (start->getY() + stop->getY()) / 2.0;
  return new Point(x, y);
}

std::vector<LineSegment> *
Geometry::getLineSegments(std::vector<Point> *points)
{
  double DISTANCE_THRESHOLD = 300.0;

  double distance;

  std::vector<LineSegment> *lineSegments = new std::vector<LineSegment>();

  Point *startCandidate = &points->at(0);
  Point *stopCandidate = &points->at(0);
  
  for (int i = i; i < points->size(); ++i) {
    distance = stopCandidate->distanceTo(&points->at(i));
    //printf("%d\n", distance);
    if (distance >= DISTANCE_THRESHOLD) {
      /* save the line segment if it's not 0 */
      if (startCandidate != stopCandidate) {
        lineSegments->push_back(LineSegment(startCandidate, stopCandidate));  
      }
      startCandidate = &points->at(i); 
    }  
    stopCandidate = &points->at(i);
    //printf("Distance between (%f, %f) and (%f, %f): %f\n", stopCandidate->getX(), stopCandidate->getY(), points->at(i).getX(), points->at(i).getY(), distanceTo);
  }

  if (startCandidate != stopCandidate) {
    lineSegments->push_back(LineSegment(startCandidate, stopCandidate));  
  }
  return lineSegments;

  //define initial starting vector location for distance analysis
  double startpoint = 0;

  //calculate distances between points and detirmine if line segment
  for (double endpoint = 1; endpoint < points->size(); endpoint++){
    LineSegment intermediatesegment(&points->at(endpoint-1), &points->at(endpoint));

    //define condition at which the distance between consecutive points is large
    //enough to be considered a seperate line
    if (intermediatesegment.getLength() > 10000){
      LineSegment discoveredsegment(&points->at(startpoint), &points->at(endpoint - 1));
      LineSegment Savedsegment = discoveredsegment;
    //	if (discoveredsegment.)
      //test to see if discovered line segment consists of consecutive points, if so do not add to linesegment vector
      if ((endpoint - 1) - startpoint > 1){
        std::cout << "start" << points->at(startpoint).getX() << ", " << points->at(startpoint).getY() << std::endl;
        std::cout << "end" << points->at(endpoint - 1).getX() << ", " << points->at(endpoint - 1).getY() << std::endl;
        lineSegments->push_back(discoveredsegment);
      }
      startpoint = endpoint;
    }


    //add in condition for when the loop reaches the end of the Points vector to conclude last line segment
    if (endpoint == points->size() - 1){
      LineSegment finalsegment(&points->at(startpoint), &points->at(endpoint));
      //test to see if discovered line segment consists of consecutive points, if so do not add to linesegment vector
      if (endpoint-startpoint > 1){
        std::cout << "start" << points->at(startpoint).getX() << ", " << points->at(startpoint).getY() << std::endl;
        std::cout << "end" << points->at(endpoint - 1).getX() << ", " << points->at(endpoint - 1).getY() << std::endl;
        lineSegments->push_back(finalsegment);
      }
    }
  }
  return lineSegments;
  //display values of length and Center
 
 /*
  for (double linesample = 0; linesample < LineSegments.size(); linesample++){
    std::cout << "Length= " << LineSegments[linesample].getlength() << " Center="<<LineSegments[linesample].getcenter().getx() << ", " << LineSegments[linesample].getcenter().gety()<<std::endl;
  }

  std::cout << std::endl;
 */ 
 /*
  //test to see if the center of two line segments is within desired seperation
  for (double firstlinesegment = 0; firstlinesegment < LineSegments.size()-1; firstlinesegment++){
    for (double secondlinesegment = firstlinesegment+1; secondlinesegment < LineSegments.size(); secondlinesegment++){
      LineSegment segmentseperation;
      segmentseperation.DefineLineSegment(&LineSegments[firstlinesegment].getcenter(), &LineSegments[secondlinesegment].getcenter());
      if (10<segmentseperation.getlength() && segmentseperation.getlength()<10){
        PotentialCandidates.push_back(segmentseperation);
        //display information on potential linesegments for leg detection
      //	std::cout << "Length= " << segmentseperation.getlength() << " Center=" << segmentseperation.getcenter().getx() << ", " << segmentseperation.getcenter().gety() << std::endl;
      }
    }
  }	
  std::cout << std::endl;
  //
  //std::cout << "Length= 37.5 Center=231.25, 350";
  // */
}

void
Geometry::dumpPoints(std::vector<Point> *points)
{
  for (int i = 0; i < points->size(); ++i) {
    printf("%f %f\n", points->at(i).getX(), points->at(i).getY()); 
  }
}

void
Geometry::dumpLineSegments(std::vector<LineSegment> *lineSegments)
{
  for (int i = 0; i < lineSegments->size(); ++i) {
    printf("Start: %f %f \t Stop: %f %f, Length: %f\n", 
      lineSegments->at(i).getStart()->getX(),
      lineSegments->at(i).getStart()->getY(),
      lineSegments->at(i).getStop()->getX(),
      lineSegments->at(i).getStop()->getY(),
      lineSegments->at(i).getLength()
    );
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

