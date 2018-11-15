#ifndef MoveRobot_h
#define MoveRobot_h
//The goal of this class is to provide functions to drive the robot

#include <Arduino.h>

class MoveRobot {
public:
  void start();
  void repeat();
  void forward();
  void back();
  void left();
  void right();
  void stop();

};


#endif
