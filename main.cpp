int
main(int argc, char **argv) 
{
  printf("start");
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
