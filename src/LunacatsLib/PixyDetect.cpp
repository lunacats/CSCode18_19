#include "PixyDetect.h"
#include <Pixy2.h>

#define FORWARD 0
#define LEFT 1
#define RIGHT 2
#define BACK 3
#define STOP 4

// -------------------------------------------------------- SETTINGS FOR AUTONOMY --------------------------------------------------------
int miningSite[2] = {100,100}; //location of the mining site
int maxDistanceVary = 50; //Maximum variation for position at mining site
int maxRobotDistance = 5000; //Maximum distance robot can be from the camera
int minRobotDistance = 10; //minimum distance robot can be from camera
int robotRotationVary = 15; //radius for the mining site zone
// -------------------------------------------------------- SETTINGS FOR AUTONOMY THAT SHOULDN'T NEED TO CHANGE --------------------------
float cameraPerspective = 5.0f; //The perspective of the Pixy Camera
int paperWidth = 100; //width of the paper mounted on the robot
int paperHeight = 50; //height of the paper mounted on the robot
// -------------------------------------------------------- SETTINGS FOR AUTONOMY END ----------------------------------------------------

//The direction the robot should go, updated in repeat
int robotDirection = STOP;
//help determine whether the robot is tilted
int lastPixyBoxCenter = 0;

//The actual pixy cam
Pixy2 pixy;

/** Initializes the pixy camera */
void PixyDetect::start() {
  pixy.init();
}

/** gets the distance from the pixy cam to the robot */
int getRobotDistance() {
  return 0;
}

/**
 * determines if the tilt of the robot is beyond the tilting threshhold
 * @param robotDistance ???
 * @return amount tilted
 */
bool getRobotTilted(int robotDistance) {
  return false;
}

/** determines whether the robot is tilted left or right based on movement */
bool robotTiltedLeft() {

}

/** tells the robot to drive in such a way where the robot won't be tilted*/
void removeTilt() {
  if(robotTiltedLeft()) {
    robotDirection = RIGHT;
  }
  else {
    robotDirection = LEFT;
  }
}


/**
 * Determines which direction the robot should go,
 *      for now it just makes the robot go the distance
 *      miningSite[0] away from the camera
 */
void PixyDetect::repeat() {
  //Read robot position and determine whether or not you turned left
  int robotDistance = getRobotDistance();
  bool robotTilted = getRobotTilted(robotDistance);

  //First make sure the robot isn't the maximum or minimum distance away
  if(robotDistance > maxRobotDistance) {
    if(!robotTilted) {
      robotDirection = BACK;
    }
    else {
      removeTilt();
    }
  }
  else if(robotDistance < minRobotDistance) {
    if(!robotTilted) {
      robotDirection = FORWARD;
    }
    else {
      removeTilt();
    }
  }

  //Then drive the robot miningSite[0] away
  else if(robotDistance - maxDistanceVary > miningSite[0]) {
    if(!robotTilted) {
      robotDirection = BACK;
    }
    else {
      removeTilt();
    }
  }
  else if(robotDistance + maxDistanceVary < miningSite[0]) {
    if(!robotTilted) {
      robotDirection = FORWARD;
    }
    else {
      removeTilt();
    }
  }
  else {
    robotDirection = STOP;
  }
}


/**
 * Determines if the robot should go forward
 * @return whether or not the robot should go forward
 */
bool PixyDetect::forward() {
  return robotDirection == FORWARD;
}

/**
 * Determines if the robot should go backwards
 * @return whether or not the robot should go back
 */
bool PixyDetect::back() {
  return robotDirection == BACK;
}

/**
 * Returns whether or not the robot should go left
 * @return o
 */
bool PixyDetect::left() {
  return robotDirection == LEFT;
}

/**
 * Returns whether or not the robot should go right
 * @return
 */
bool PixyDetect::right() {
  return robotDirection == RIGHT;
}
