#include "MoveRobot.h"
#include <Servo.h>

//------------------------- Actions --------------------------------------//
// Change the Hex to match the controller actions (buttons etc..)
#define LEFT_FWD 0xD6
#define LEFT_NEUTRAL 0xD0
#define LEFT_REV 0xD8
#define RIGHT_FWD 0xDB
#define RIGHT_NEUTRAL 0xD5
#define RIGHT_REV 0xDD
#define FRAME_UP 0xB8
#define FRAME_DOWN 0xB6
#define CBELT_ON 0xD1
#define CBELT_REV 0xD3
#define AUG_ON 0xB3
#define AUG_REV 0xB4
#define AUG_UP 0xB5
#define AUG_DOWN 0xB7
#define AUTO_MINE 0xB2
#define E_STOP 0xB1
#define WHEEL_TOGGLE 0xD4
//------------------------- Pins ----------------------------------------//
//Motors
#define LDRIVE_PIN 9
#define RDRIVE_PIN 10

//-------------------------MISC---------------------------------------
// The numbers are based on servo angles 0'-180'. For our case, 90' is NEUTRAL. Some buffer is given on either side.
#define POS 170 //FULL Forward
#define NEUTRAL 92 //STOP on VICTOR this number may have to be calibrated...
#define NEG 10 //FULL Reverse

#define WHEEL_MOD_POS 110 // slower than 170
#define WHEEL_MOD_NEG 70 // slower than 45

//-----------------------Servos-----------------
Servo Ldrive;
Servo Rdrive;



//converts power from -90 to 90 to 0 to 180 and makes sure power is in range
int convertP(int pow)
{
  if(pow < -90 || pow  > 90) {
    Serial.print("Error, pow:");
    Serial.print(pow);
    Serial.println(" is out of range");
    return 90;
  }

  int nPow = pow + 90;
  return nPow;
}

void drive(int lPower, int rPower) {
  Ldrive.write(convertP(lPower));
  Rdrive.write(convertP(rPower));
}

void MoveRobot::start(short lPin, short rPin) {
  Ldrive.attach(lPin);
  Rdrive.attach(rPin);
}

void MoveRobot::forward(int power) {
    drive(power,power);
}

void MoveRobot::back(int power) {
  drive(-power,-power);
}

void MoveRobot::left(int power) {
  drive(-power,power);
}

void MoveRobot::right(int power) {
  drive(power,-power);
}

void MoveRobot::stop() {
  drive(2,2);
}

void MoveRobot::forward(int power, int timing) {
    forward(power);
    delay(timing);
    stop();
}
void MoveRobot::left(int power, int timing) {
    left(power);
    delay(timing);
    stop();
}
void MoveRobot::right(int power, int timing) {
    right(power);
    delay(timing);
    stop();
}
void MoveRobot::back(int power, int timing) {
    back(power);
    delay(timing);
    stop();
}

// void MoveRobot::leftPow(int lpower, int rPower) {
//   drive(-lPower,rPower);
// }
//
// void MoveRobot::rightPow(int lpower, int rPower) {
//   drive(lPower,-lPower);
// }
// void MoveRobot::left(int lPower, int rPower, int timing) {
//   drive(-lPower,rPower);
//   delay(timing);
// }
// void MoveRobot::right(int lPower, int rPower, int timing) {
//   drive(lPower,-rPower);
//   delay(timing);
// }
