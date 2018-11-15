#ifndef FlashWhenRecieveCom_h
#define FlashWhenRecieveCom_h

#include <Arduino.h>
//The goal of this class is to flash light 13 when a message is sent or recieved

class FlashWhenRecieveCom {

public:
  void start();
  void repeat();

};

#endif
