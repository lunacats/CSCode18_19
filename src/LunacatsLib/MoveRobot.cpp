#include "MoveRobot.h"
#include <Servo.h>
#include <zconf.h>

//------------------------------- Actions ------------------------------//
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
//-------------------------------- Pins --------------------------------//
//Motors
#define LDRIVE_PIN 12
#define RDRIVE_PIN 13
#define LACT_PIN 11
#define RACT_PIN 10
#define CBELT_PIN 9
#define AUGPWR_PIN 8
#define AUGDIR_PIN 7
#define BSCRUP_PIN 5 //had to change. broke a pin off in 6
#define BSCRDN_PIN 4
#define LIMSWUP_PIN 3
#define LIMSWDN_PIN 2
//Limit Switches     I hope we have have enough pins left for these.
#define A_up 0
#define A_down 0

//-------------------------------- MISC --------------------------------//
// The numbers are based on servo angles 0'-180'. For our case, 90' is NEUTRAL. Some buffer is given on either side.
#define POS 170 //FULL Forward
#define NEUTRAL 92 //STOP on VICTOR this number may have to be calibrated...
#define NEG 10 //FULL Reverse
#define P_MOD 140 //Allows matching of actuator speeds.
#define N_MOD 45
#define OFF LOW
#define ON HIGH
#define UP 1
#define DOWN -1
#define wait 1000
#define WHEEL_MOD_POS 110 // slower than 170
#define WHEEL_MOD_NEG 70 // slower than 45

//------------------------------- Servos -------------------------------//
//motor servos
Servo Ldrive;
Servo Rdrive;
Servo Lact;
Servo Ract;
Servo Cbelt;

//???
int toggleFrameUp = 0;
int toggleFrameDown = 0;
int toggleAugOn = 0;
int toggleAugRev = 0;
int toggleAugUp = 0;
int toggleAugDown = 0;
int toggleConveyerOn = 0;
int toggleConveyerRev = 0;
int toggleWheelSpeed = 0;

/**
 * Convert the range of power given to the motor
 * from ( -90 : 90 ) to ( 0: 180 )
 *
 * The motors work between the range of ( 0: 180 ) where
 * the values 0 - 89 make the robot go backwards
 * the values 91 - 180 make the robot go forward.
 *
 * Changing the range helps conceptualize the direction
 * that the robot is moving
 * (negative = backwards, pos = forwards)
 *
 * @param p power to motor where -90 < p < 90
 * @return power to motor where 0 < p < 180
 */
short MoveRobot::powerConvert(short p){
    return p + (short)90;
}

/**
 * Move the robot with a given power
 * @param rPower power to right motor between -90 < rPower < 90
 * @param lPower power to left motor between -90 < lPower < 90
 */
void MoveRobot::drive(short rPower, short lPower) {
    Ldrive.write(powerConvert(lPower));
    Rdrive.write(powerConvert(rPower));
}

/**
 * Move the robot forward at given power
 * @param power speed between -90 < power < 90
 */
void MoveRobot::move_powerForward(short power) {
    drive(power,power);
}

/**
 * Move the robot backwards at given power
 * @param power speed between -90 < power < 90
 */
void MoveRobot::move_powerBack(short power) {
    drive(-power,-power);
}

/**
 * Turn the robot left at given power
 * @param power speed between -90 < power < 90
 */
void MoveRobot::move_powerLeft(short power) {
    drive(power,-power);
}

/**
 * Turn the robot right at given power
 * @param power speed between -90 < power < 90
 */
void MoveRobot::move_powerRight(short power) {
    drive(-power, power);
}

/*
** Stop the robot from moving
void MoveRobot::stop() {
    drive(0,0);
}
*/
/**
 * Move the robot for a given amount of time in milliseconds
 *
 * @param movement - how the robot will move (i.e. one of the move_ functions)
 * @param power - the power the robot will move at
 * @param milliseconds - the time the robot will move
 */
void MoveRobot::driveFor( void (MoveRobot::*movement)(short),
        short power, unsigned int milliseconds ) {
    (this->*movement)(power);
    sleep(milliseconds);
}

/**
 * Turn 90 degrees based on estimated time
 *
 * NOTE: NOT TESTED
 *      Example implementation of driveFor
 */
void MoveRobot::turnLeft_90_Time() {
   driveFor(&MoveRobot::move_powerLeft, WHEEL_MOD_NEG, 1000);
}

/*
MoveRobot wheels = MoveRobot();
void main() {

    wheels.Forward(30);
    sleep(1000);
    wheels.stop();
    sleep(1000);
    wheels.right(90);
    sleep(1000);
    wheels.stop();
}
*/

/** ??? */
void MoveRobot::repeat() {

}

/** move both wheels in the same direction (forward)*/
void MoveRobot::forward() {
    Ldrive.write(WHEEL_MOD_NEG);
    Rdrive.write(WHEEL_MOD_NEG);
}

/** move both wheels in the same direction (backward)*/
void MoveRobot::back() {
  Ldrive.write(WHEEL_MOD_POS);
  Rdrive.write(WHEEL_MOD_POS);
}

/** move the left wheel backwards and the right wheel forward*/
void MoveRobot::left() {
  Ldrive.write(WHEEL_MOD_POS);
  Rdrive.write(WHEEL_MOD_NEG);
}

/** move the left wheel forward and the right wheel backwards*/
void MoveRobot::right() {
  Ldrive.write(WHEEL_MOD_NEG);
  Rdrive.write(WHEEL_MOD_POS);
}

/**s top the wheels from moving*/
void MoveRobot::stop() {
  Ldrive.write(NEUTRAL);
  Rdrive.write(NEUTRAL);
}

// ==================== OLD CODE ==================== //
//
// /* function to move the left drive forward */
// void leftForward() {
//   if (digitalRead(LIMSWUP_PIN) == LOW) { // only allow the wheels to move if the auger is tripping the limit switches
//     if (toggleWheelSpeed) {
//       Ldrive.write(WHEEL_MOD_POS);
//     } else {
//       Ldrive.write(POS);
//     }
//   }
// }
//
// void leftNeutral() {
//   Ldrive.write(NEUTRAL);
// }
//
// /* function to move the left drive in reverse */
// void leftReverse() {
//   if (digitalRead(LIMSWUP_PIN) == LOW) { // only allow the wheels to move if the auger is tripping the limit switches
//     if (toggleWheelSpeed) {
//       Ldrive.write(WHEEL_MOD_NEG);
//     } else {
//       Ldrive.write(NEG);
//     }
//   }
// }
//
// /* function to move the right drive forward */
// void rightForward() {
//   if (digitalRead(LIMSWUP_PIN) == LOW) { // only allow the wheels to move if the auger is tripping the limit switches
//     if (toggleWheelSpeed) {
//       Rdrive.write(WHEEL_MOD_POS);
//     } else {
//       Rdrive.write(POS);
//     }
//   }
// }
// void rightNeutral() {
//   Rdrive.write(NEUTRAL);
// }
//
// /* function to move the right drive in reverse */
// void rightReverse() {
//   if (digitalRead(LIMSWUP_PIN) == LOW) {
//     if (toggleWheelSpeed) {
//       Rdrive.write(WHEEL_MOD_NEG);
//     } else {
//       Rdrive.write(NEG);
//     }
//   }
// }
//
//
// /* toggle wheel speed */
// int toggleWheelMod() {
//   if (!toggleWheelSpeed) {
//     return 1;
//   } else {
//     return 0;
//   }
// }
//
// /*
//   function to raise the frame
//   this is a toggle. it returns the value to set the global toggle to
//   @returns 1 if frame is raising, 0 if frame is stopped raising
// */
// int frameUp() {
//   if (!toggleFrameUp) {
//     Lact.write(NEG);
//     Ract.write(N_MOD); //One of the actual actuators moves at a slower rate, so PWM is modified to match speeeds.       toggleFrameUp = 1;
//     return 1;
//   } else {
//     Lact.write(NEUTRAL);
//     Ract.write(NEUTRAL);
//     return 0;
//   }
// }
//
// /*
//   function to lower the frame
//   this is a toggle
//   @returns 1 if frame is lowering, 0 if frame is stopped lowering
// */
// int frameDown() {
//   if (!toggleFrameDown) {
//     Lact.write(POS);
//     Ract.write(P_MOD); //One of the actual actuators moves at a slower rate, so PWM is modified to match speeeds.
//     return 1;
//   } else {
//     Lact.write(NEUTRAL);
//     Ract.write(NEUTRAL);
//     return 0;
//   }
// }
//
//
// int conveyerOn() {
//   if (!toggleConveyerOn) {
//     Cbelt.write(POS);
//     return 1;
//   } else {
//     Cbelt.write(NEUTRAL);
//     return 0;
//   }
// }
//
// int conveyerRev() {
//   if (!toggleConveyerRev) {
//     Cbelt.write(NEG);
//     return 1;
//   } else {
//     Cbelt.write(NEUTRAL);
//     return 0;
//   }
// }
//
// int augerOn() {
//   if (!toggleAugOn) {
//     digitalWrite(AUGPWR_PIN, ON);
//     return 1;
//   } else {
//     digitalWrite(AUGPWR_PIN, OFF);
//     return 0;
//   }
// }
//
// int augerRev() {
//   if (!toggleAugRev) {
//     digitalWrite(AUGPWR_PIN, ON);
//     digitalWrite(AUGDIR_PIN, ON);
//     return 1;
//   } else {
//     digitalWrite(AUGDIR_PIN, OFF);
//     digitalWrite(AUGPWR_PIN, OFF);
//     toggleAugOn = 0;
//     return 0;
//   }
// }
//
// int augerUp() {
//   if (!digitalRead(LIMSWUP_PIN) == LOW) {//only allows the action if it's not at the top already
//       digitalWrite(BSCRUP_PIN, HIGH); // Enables the left stepper motor to move in a particular direction
//       delay(wait);
//       digitalWrite(BSCRUP_PIN, LOW); // Enables the left stepper motor to move in a particular direction
//   }
// }
//
// int augerDown() {
// //  status_down = digitalRead(LIMSWDN_PIN);
//  if (!digitalRead(LIMSWDN_PIN) == LOW) {// only allows the action if it's not at the bottom already
//       digitalWrite(BSCRDN_PIN, HIGH); // Enables the left stepper motor to move in a particular direction
//       delay(wait);
//       digitalWrite(BSCRDN_PIN, LOW); // Enables the left stepper motor to move in a particular direction
//   }
// }
//
//
// void eStop() {
//   Ldrive.write(NEUTRAL);
//   Rdrive.write(NEUTRAL);
//   Lact.write(NEUTRAL);
//   Ract.write(NEUTRAL);
//   Cbelt.write(NEUTRAL);
//   digitalWrite(AUGPWR_PIN, OFF);
//   digitalWrite(AUGDIR_PIN, OFF);
//
//   digitalWrite(BSCRUP_PIN, OFF);
//   digitalWrite(BSCRDN_PIN, OFF);
// }
//
//
// void MoveRobot::start() {
//   //Initialize Ldrive
//   Ldrive.attach(LDRIVE_PIN);
//   Ldrive.write(NEUTRAL);
//
//   //Initialize Rdrive
//   Rdrive.attach(RDRIVE_PIN);
//   Rdrive.write(NEUTRAL);
//
//   //Initialize Lact;
//   Lact.attach(LACT_PIN);
//   Lact.write(NEUTRAL);
//
//   //Initialize Ract;
//   Ract.attach(RACT_PIN);
//   Ract.write(NEUTRAL);
//
//   //Initialize Cbelt
//   Cbelt.attach(CBELT_PIN);
//   Cbelt.write(NEUTRAL);
//
//   //Initialize AugPwr
//   pinMode(AUGPWR_PIN, OUTPUT);
//   digitalWrite(AUGPWR_PIN, OFF);
//
//    //Initialize AugDir
//   pinMode(AUGDIR_PIN, OUTPUT);
//   digitalWrite(AUGDIR_PIN, OFF);
//
//   //Initialize RightBscrDir
//   pinMode(BSCRUP_PIN, OUTPUT);
//   digitalWrite(BSCRUP_PIN, OFF);
//
//   //Initialize RightBscrDir
//   pinMode(BSCRDN_PIN, OUTPUT);
//   digitalWrite(BSCRDN_PIN, OFF);
//
//   //Initialize RightBscrDir
//   pinMode(LIMSWUP_PIN, INPUT_PULLUP);
//
//   //Initialize RightBscrDir
//   pinMode(LIMSWDN_PIN, INPUT_PULLUP);
// }
