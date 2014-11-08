#include "Aria.h"
void
run(ArRobot &robot)
{
  robot.lock();
  robot.setRotVel(100);
  robot.unlock();
  ArUtil::sleep(3*1000);
  printf("Stopping\n");
}

int
main(int argc, char **argv) 
{
  Aria::init();
  
  ArArgumentParser argParser(&argc, argv);
  argParser.addDefaultArgument("-rp /dev/ttyUSB0");
  argParser.loadDefaultArguments();

  ArRobot robot;
  ArRobotConnector con(&argParser, &robot);


  if(!Aria::parseArgs())
  {
    Aria::logOptions();
    Aria::exit(1);
    return 1;
  }

  if(!con.connectRobot())
  {
    ArLog::log(ArLog::Normal, "directMotionExample: Could not connect to the robot. Exiting.");
    if(argParser.checkHelpAndWarnUnparsed()) 
    {
      Aria::logOptions();
	}
    Aria::exit(1);
    return 1;
  }

  ArLog::log(ArLog::Normal, "directMotionExample: Connected.");
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


  // Send the robot a series of motion commands directly, sleeping for a 
  // few seconds afterwards to give the robot time to execute them.
  printf("directMotionExample: Setting rot velocity to 100 deg/sec then sleeping 3 seconds\n");
  run(robot);
  Aria::exit(0);
  return 0;
}

