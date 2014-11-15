#include "geometry.h"
#include "robolib.h"
std::vector<Point> *
RoboLib::getReadings(ArRobot &robot, ArLaser *laser)
{

  std::vector<Point> *readings = new std::vector<Point>();
  const std::list<ArSensorReading *> *raw_readings;

  laser->lockDevice();
  raw_readings = laser->getRawReadings();
  std::list<ArSensorReading *>::const_iterator it;

  if (raw_readings != NULL) {
    if ((raw_readings->end() != raw_readings->begin())) {
      for (it = raw_readings->begin(); it != raw_readings->end(); it++) {
        Point p = Point((*it)->getLocalX(),(*it)->getLocalY()); 
        readings->push_back(p);
      }
    } 
  }
  laser->unlockDevice();

  return readings;
}

void
RoboLib::dumpReadings(std::vector<Point> *readings)
{
  for (int i = 0; i < readings->size(); ++i) {
    printf("%f %f\n", readings->at(i).getX(), readings->at(i).getY()); 
  }
}

std::vector<Point> *
RoboLib::getReadingsFromFile(char *filename)
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
