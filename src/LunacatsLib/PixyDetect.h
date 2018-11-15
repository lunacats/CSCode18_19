#ifndef PixyDetect_h
#define PixyDetect_h
//The goal of this class is to provide functions to drive the robot

#include <Arduino.h>

class PixyDetect {
public:
  void start();
  void repeat();
  bool forward();
  bool back();
  bool left();
  bool right();

};


#endif
