#include <vector>
#include "geometry.h"
#include "Aria.h"
class RoboLib {
  public:
    static std::vector<Point> * getReadings(ArRobot &robot, ArLaser *laser);
    static std::vector<Point> * getReadingsFromFile(char *filename);
    static void dumpReadings(std::vector<Point> *readings);

};
