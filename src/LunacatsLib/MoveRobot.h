#ifndef MoveRobot_h
#define MoveRobot_h
//The goal of this class is to provide functions to drive the robot

#include <Arduino.h>

class MoveRobot {
public:
  void start(short lPin, short rPin);
  void repeat();

  void leftPow (int lPower, int rPower, int timing);
  void rightPow(int lPower, int rPower, int timing);

  void forward(int power, int timing);
  void back   (int power, int timing);
  void left   (int power, int timing);
  void right  (int power, int timing);

  void forward(int power);
  void back   (int power);
  void left   (int power);
  void right  (int power);
  void stop   ();

};


#endif
