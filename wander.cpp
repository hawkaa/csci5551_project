/*
Adept MobileRobots Robotics Interface for Applications (ARIA)
Copyright (C) 2004, 2005 ActivMedia Robotics LLC
Copyright (C) 2006, 2007, 2008, 2009, 2010 MobileRobots Inc.
Copyright (C) 2011, 2012, 2013 Adept Technology

     This program is free software; you can redistribute it and/or modify
     it under the terms of the GNU General Public License as published by
     the Free Software Foundation; either version 2 of the License, or
     (at your option) any later version.

     This program is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU General Public License for more details.

     You should have received a copy of the GNU General Public License
     along with this program; if not, write to the Free Software
     Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

If you wish to redistribute ARIA under different terms, contact 
Adept MobileRobots for information about a commercial version of ARIA at 
robots@mobilerobots.com or 
Adept MobileRobots, 10 Columbia Drive, Amherst, NH 03031; +1-603-881-7960
*/
#include "Aria.h"


/** @example wander.cpp 
 * Example using actions and range devices to implement a random wander avoiding obstacles.
 *
 *  This program will just have the robot wander around. It uses some avoidance 
 *  actions if obstacles are detected with the sonar or laser (if robot has a
 *  laser), otherwise it just has a constant forward velocity.
 * 
 *  Press Control-C or Escape keys to exit.
 *  
 * This program will work either with the MobileSim simulator or on a real
 * robot's onboard computer.  (Or use -remoteHost to connect to a wireless
 * ethernet-serial bridge.)
*/


int main(int argc, char **argv)
{
  Aria::init();
  ArRobot robot;

  ArSerialConnection serialConnection;
  ArTcpConnection tcpConnection;
    
  if (tcpConnection.open("localhost", 8101)) {
    robot.setDeviceConnection(&tcpConnection);
  } else {
    serialConnection.setPort("/dev/ttyUSB0");
    robot.setDeviceConnection(&serialConnection);
  }
  robot.blockingConnect();
   
  printf("Setting robot to run async\n");
  robot.runAsync(false);

  printf("Turning off sound\n");
  robot.comInt(ArCommands::SOUNDTOG, 0);

  printf("Enabling motors\n");
  robot.enableMotors();

  // add a set of actions that combine together to effect the wander behavior
  /*ArActionStallRecover recover;
  ArActionBumpers bumpers;
  ArActionAvoidFront avoidFrontNear("Avoid Front Near", 225, 0);
  ArActionAvoidFront avoidFrontFar;
  ArActionConstantVelocity constantVelocity("Constant Velocity", 400);
  robot.addAction(&recover, 100);
  robot.addAction(&bumpers, 75);
  robot.addAction(&avoidFrontNear, 50);
  robot.addAction(&avoidFrontFar, 49);
  robot.addAction(&constantVelocity, 25);*/

  printf("Locking\n");
  robot.lock();
  robot.setVel(100.0);
  robot.unlock();
  printf("Sleeping\n");
  ArUtil::sleep(3*1000);
  printf("Awake\n");

  
  // wait for robot task loop to end before exiting the program
  //while (true);
  //robot.waitForRunExit();
  

  Aria::exit(0);
  return 0;
}
