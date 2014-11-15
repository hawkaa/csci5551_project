
#include <iostream>

#include "Aria.h"
#include "lib/robolib.h"
class
Point {
    int x;
    int y;
  public:
    Point(int x, int y) {
      this->x = x;
      this->y = y;
    }
};

void
run(ArRobot &robot, ArLaser *laser)
{
  ArUtil::sleep(500); /* get some readings */
  printf("Performing SICK scan\n");
  const std::list<ArSensorReading *> *readings;
  laser->lockDevice();
  readings = laser->getRawReadings();
  std::list<ArSensorReading *>::const_iterator it;
  int x, y;

  ArSensorReading halfReading;
  int i = 0;
  if (readings != NULL) {
    if ((readings->end() != readings->begin())) {
      for (it = readings->begin(); it != readings->end(); it++) {
        if (i == 179) {
          x = (*it)->getLocalX();
          y = (*it)->getLocalY();
        }
        std::cout << (*it)->getLocalX() << ", " << (*it)->getLocalY() << std::endl;
        ++i;
      }
      std::cout << std::endl;
    } else {
      std::cout << "(readings->end() == readings->begin())" << std::endl;
    } 
  } else {
    std::cout << "NULL == readings" << std::endl;
  }

  laser->unlockDevice();
  printf("Aiming for %i, %i\n", x, y);
  ArPose pos = ArPose(x,y);
  double distance = robot.findDistanceTo(pos);
  printf("distance: %f\n", distance);

  robot.lock();
  robot.move(distance);
  robot.unlock();

  while (!robot.isMoveDone()) {
    ArUtil::sleep(500);
  }
  

  

}

int
main(int argc, char **argv) 
{
  Aria::init();
  
  ArArgumentParser argParser(&argc, argv);
  argParser.loadDefaultArguments();
  argParser.addDefaultArgument("-rp /dev/ttyUSB0");
  argParser.addDefaultArgument("-lp /dev/ttyUSB1");
  argParser.addDefaultArgument("-connectLaser -laserDegrees 180 -laserIncrement half");
  argParser.loadDefaultArguments();

  ArRobot robot;
  ArRobotConnector robotConnector(&argParser, &robot);
  ArLaserConnector laserConnector(&argParser, &robot, &robotConnector);

  if(!robotConnector.connectRobot())
  {
    ArLog::log(ArLog::Normal, "directMotionExample: Could not connect to the robot. Exiting.");
    if(argParser.checkHelpAndWarnUnparsed()) 
    {
      Aria::logOptions();
	}
    Aria::exit(1);
    return 1;
  }


  if(!Aria::parseArgs() || !argParser.checkHelpAndWarnUnparsed())
  {
    Aria::logOptions();
    Aria::exit(1);
  }



  // Run the robot processing cycle in its own thread. Note that after starting this
  // thread, we must lock and unlock the ArRobot object before and after
  // accessing it.
  robot.runAsync(false);
  robot.enableMotors();
  ArUtil::sleep(500);

  if(!laserConnector.connectLasers(false, false, true))
  {
    ArLog::log(ArLog::Terse, "sickLogger: Error: Could not connect to laser(s).  Use -help to list options.");
    Aria::exit(3);
  }
  ArLog::log(ArLog::Normal, "directMotionExample: Connected.");
  if(!Aria::parseArgs() || !argParser.checkHelpAndWarnUnparsed())
  {
    Aria::logOptions();
    Aria::exit(1);
  }

  // Send the robot a series of motion commands directly, sleeping for a 
  // few seconds afterwards to give the robot time to execute them.
  printf("directMotionExample: Setting rot velocity to 100 deg/sec then sleeping 3 seconds\n");

  ArLaser *laser = robot.findLaser(1);
  printf("Laser Address: %x\n", laser);
  laser->runAsync();
  run(robot, laser);
  Aria::exit(0);
  return 0;
}

