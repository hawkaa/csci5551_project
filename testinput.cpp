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
  
  std::vector<LineSegment> *lineSegments = Geometry::getLineSegments(points);
  Geometry::dumpLineSegments(lineSegments);


  delete points;
  delete lineSegments;
}
