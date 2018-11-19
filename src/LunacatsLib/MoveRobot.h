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

  short powerConvert(short p);
  void drive(short rPower, short lPower);
  void move_powerForward(short power);
  void move_powerBack(short power);
  void move_powerLeft(short power);
  void move_powerRight(short power);
  void driveFor(void (MoveRobot::*movement)(short), short power, unsigned int milliseconds);
  void turnLeft_90_Time();
};


#endif
