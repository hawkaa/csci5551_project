#include <cstdio>
#include <vector>

#include "geometry.h"
#include "robolib.h"

int
main(int argc, char **argv)
{
  char *filename = argv[1];
  std::vector<Point> *points = Geometry::getPointsFromFile(filename);
  Geometry::dumpPoints(points);
 
  std::vector<LineSegment> *lineSegments = Geometry::getLineSegments(points, 50.0);
  printf("-- ORIGINAL LINE SEGMENTS --\n");
  Geometry::dumpLineSegments(lineSegments);

  Geometry::filterByLength(lineSegments, 50.0, 200.0);

  printf("-- LENGTH FILTERED LINE SEGMENTS --\n");
  Geometry::dumpLineSegments(lineSegments);

  std::vector<Point> *centroids = Geometry::getCentroids(lineSegments);
  printf("-- CENTROIDS --\n");
  Geometry::dumpPoints(centroids);

  std::vector<LineSegment> *legs = Geometry::getLegs(centroids, 50.0, 500.0);

  printf("-- LEGS --\n");
  Geometry::dumpLineSegments(legs);

  delete points;
  delete lineSegments;
  delete legs;
}
