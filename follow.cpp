#include <iostream>
#include <cstdio>

#include "Aria.h"
#include "robolib.h"
#include "geometry.h"

const static double KISS_HOUGH_TRESHOLD = 80.0;
const static double SEGMENT_LENGTH_MINIMUM = 95.0;
const static double SEGMENT_LENGTH_MAXIMUM =150.0;
const static double KISS_MATCH_MINIMUM = 50.0;
const static double KISS_MATCH_MAXIMUM = 300.0;
const static double ZONE_0_PERIMITER = 1000.0;
const static double ZONE_1_PERIMITER = 1200.0;
const static double ZONE_2_PERIMITER = 2000.0;
const static double LOW_SPEED_TIER = 350.0;
const static double HIGH_SPEED_TIER = 1000.0;

static Point *
getPosition(ArRobot &robot)
{
  ArPose pos = robot.getPose();
  printf("Robot position: %f, %f\n", pos.getX(), pos.getY());
  return new Point(pos.getX(), pos.getY());;
}

static Point *
getLegs(ArRobot &robot, ArLaser *laser)
{
  /* readings */
  std::vector<Point> *points = RoboLib::getReadings(robot, laser);
  //printf("%d\n", points->size());
  //Geometry::dumpPoints(points, NULL);

  /* KISS Hough */
  std::vector<LineSegment> *lineSegments = Geometry::getLineSegments(points, KISS_HOUGH_TRESHOLD);
  /*printf("-- ORIGINAL LINE SEGMENTS --\n");
  Geometry::dumpLineSegments(lineSegments, NULL);
  printf("\n");*/

  /* Length filter */
  Geometry::filterByLength(lineSegments, SEGMENT_LENGTH_MINIMUM, SEGMENT_LENGTH_MAXIMUM);
  /*printf("-- LENGTH FILTERED LINE SEGMENTS --\n");
  Geometry::dumpLineSegments(lineSegments, NULL);
  printf("\n");*/

  /* get centroids */
  std::vector<Point> *centroids = Geometry::getCentroids(lineSegments);

  /* KISS Match */
  std::vector<LineSegment> *legs = Geometry::getLegs(centroids, 50.0, 300.0);
  /*printf("-- LEGS --\n");
  Geometry::dumpLineSegments(legs, NULL);
  printf("\n");*/

  /* Closest */
  Point *origin = new Point(0.0, 0.0);
  Point *closest = Geometry::getClosest(legs, origin);

  delete points;
  delete lineSegments;
  delete centroids;
  delete legs;
  delete origin;

  return closest;
  
}

void
run(ArRobot &robot, ArLaser *laser)
{
  /* goto action */
  ArActionGoto gotoAction("goto", ArPose(0.0, 0.0, 0.0), 100.0, 400.0, 500.0, 7);
  robot.addAction(&gotoAction, 50);

  /* stop action */
  ArActionStop stopAction("stop");
  robot.addAction(&stopAction, 40);
  
  /* sleep to get some reading */
  ArUtil::sleep(5000);
  Point *closest;
  Point *origin = new Point(0.0, 0.0);
  double actualDistance, travelDistance;
  Point intermediate;
  while (true) {
    /* scan */
    printf(" -- SCAN -- \n");
    closest = getLegs(robot, laser);
    if (closest != NULL) {

      /* print data */
      printf("Found legs at (%f, %f)\n", closest->getX(), closest->getY()); 

       
      /* calculate intermediate point */
      actualDistance = origin->distanceTo(closest);

      /* set speed */
      if (actualDistance <= ZONE_2_PERIMITER) {
        printf("SPEED LOW TIER\n");
        gotoAction.setSpeed(LOW_SPEED_TIER);
      } else {
        printf("SPEED HIGH TIER\n");
        gotoAction.setSpeed(HIGH_SPEED_TIER);
      }


      travelDistance = actualDistance - ZONE_0_PERIMITER;
      if (travelDistance > ZONE_1_PERIMITER - ZONE_0_PERIMITER) {
        printf("ZONE 2+\n");
        /* reset */
        robot.moveTo(ArPose(0.0, 0.0, 0.0));
        gotoAction.setGoal(ArPose((travelDistance / actualDistance) * closest->getX(), (travelDistance / actualDistance) * closest->getY()));

      } else if (travelDistance <= 0.0) {
        printf("ZONE 0\n");
        gotoAction.cancelGoal();
      } else {
        printf("ZONE 1\n");
      }
    } else {
      printf("No legs found\n");
    }
    printf("\n\n");
    delete closest;
    ArUtil::sleep(500); /* get some readings */
  }



}

#include "main.cpp"
