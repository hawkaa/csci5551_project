#include <iostream>

#include "Aria.h"
#include "robolib.h"
#include "geometry.h"

void
run(ArRobot &robot, ArLaser *laser)
{
  ArUtil::sleep(500); /* get some readings */

  std::vector<Point> *readings = RoboLib::getReadings(robot, laser);

  RoboLib::dumpReadings(readings);

  delete readings;

}

#include "main.cpp"
