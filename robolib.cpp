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

