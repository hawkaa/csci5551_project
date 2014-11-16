#include <iostream>
#include <cstdio>

#include "Aria.h"
#include "robolib.h"
#include "geometry.h"


void
run(ArRobot &robot, ArLaser *laser)
{

  FILE *rh, *ph, *lh, *lh2, *lh3;
  
  rh = fopen("robot.txt", "w");
  ph = fopen("points.txt", "w");
  lh = fopen("linesegments.txt", "w");
  lh2 = fopen("length_linesegments.txt", "w");
  lh3 = fopen("legs.txt", "w");

  robot.lock();
  ArPose pos = robot.getPose();
  fprintf(rh, "%f %f\n", pos.getX(), pos.getY());
  robot.unlock();
  ArUtil::sleep(5000); /* get some readings */
  

    
  std::vector<Point> *points = RoboLib::getReadings(robot, laser);
  Geometry::dumpPoints(points, ph);


  std::vector<LineSegment> *lineSegments = Geometry::getLineSegments(points, 100.0);
  printf("-- ORIGINAL LINE SEGMENTS --\n");
  Geometry::dumpLineSegments(lineSegments, lh);

  Geometry::filterByLength(lineSegments, 110.0, 200.0);

  printf("-- LENGTH FILTERED LINE SEGMENTS --\n");
  Geometry::dumpLineSegments(lineSegments, lh2);

  std::vector<Point> *centroids = Geometry::getCentroids(lineSegments);
  printf("-- CENTROIDS --\n");
  Geometry::dumpPoints(centroids, NULL);

  std::vector<LineSegment> *legs = Geometry::getLegs(centroids, 50.0, 300.0);

  printf("-- LEGS --\n");
  Geometry::dumpLineSegments(legs, lh3);


  delete points;
  delete lineSegments;
  delete centroids;
  delete legs;
  fclose(rh);
  fclose(ph);
  fclose(lh);

}

#include "main.cpp"
