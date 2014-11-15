#include <cstdio>
#include <vector>

#include "geometry.h"
#include "robolib.h"

int
main(int argc, char **argv)
{
  char *filename = argv[1];
  std::vector<Point> *readings = RoboLib::getReadingsFromFile(filename);
  RoboLib::dumpReadings(readings);
  delete readings;
}
