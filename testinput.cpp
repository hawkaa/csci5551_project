#include <cstdio>
#include <vector>

#include "geometry.h"
#include "robolib.h"

int
main(int argc, char **argv)
{
  char *filename = argv[1];
  std::vector<Point> *points = Geometry::getPointsFromFile(filename);
  Geometry::dumpPoints(points, NULL);
 
  std::vector<LineSegment> *lineSegments = Geometry::getLineSegments(points, 100.0);
  printf("-- ORIGINAL LINE SEGMENTS --\n");
  Geometry::dumpLineSegments(lineSegments, NULL);

  Geometry::filterByLength(lineSegments, 110.0, 200.0);

  printf("-- LENGTH FILTERED LINE SEGMENTS --\n");
  Geometry::dumpLineSegments(lineSegments, NULL);

  std::vector<Point> *centroids = Geometry::getCentroids(lineSegments);
  printf("-- CENTROIDS --\n");
  Geometry::dumpPoints(centroids, NULL);

  std::vector<LineSegment> *legs = Geometry::getLegs(centroids, 50.0, 300.0);

  printf("-- LEGS --\n");
  Geometry::dumpLineSegments(legs, NULL);
  
  printf("-- PAIR --\n");
  Point *robot = new Point(0.0, 0.0);
  Point *centerpoint = Geometry::getClosest(legs, robot);
  if (centerpoint == NULL) {
    printf("NO PAIR\n");
  } else {
    printf("PAIR AT %f %f", centerpoint->getX(), centerpoint->getY()); 
  }
  

  delete points;
  delete lineSegments;
  delete centroids;
  delete legs;
  delete robot;
}
