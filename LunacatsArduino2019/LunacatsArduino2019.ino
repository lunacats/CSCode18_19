#include <ArduinoJson.h>
#include <MoveRobot.h>
//#include <Wire.h>
//#include <SparkFun_VL6180X.h>

#define FORWARD 0
#define BACK 1
#define LEFT 2
#define RIGHT 3
#define STOP 4
#define GETPIXY 5
#define GETLIDAR 6

#define VL6180X_ADDRESS 0x29

String buff;
MoveRobot robot;

//VL6180xIdentification identification;
//VL6180x lidar(VL6180X_ADDRESS);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(2000000);
  Serial.setTimeout(50);
  robot.start(10,11);

//  Wire.begin(); //Start I2C library
//  delay(100); // delay .1s
//  
//  lidar.getIdentification(&identification); // Retrieve manufacture info from device memory
//
//  if(lidar.VL6180xInit() != 0){
//    Serial.println("FAILED TO INITALIZE"); //Initialize device and check for errors
//  }; 
//  
//  lidar.VL6180xDefautSettings(); //Load default settings to get started.
//  
//  delay(1000); // delay 1s
}



enum DriveCommand {
  forward = FORWARD,
  back = BACK,
  left = LEFT,
  right = RIGHT,
  stop = STOP
};

DriveCommand lastCommand = stop;



void parseCommand() {

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(buff);

  // Test if parsing succeeds.
  if (!root.success()) {
    Serial.println("{'error':'Bad Command', 'cmd':'"+buff+"'}");
    return;
  }
  
  if(root["c"] == 6) {
//    Serial.println("{\"L\":" + String(getLidarInches()) + "}");
    Serial.println("{\"L\":9999}");
  }
  else {
    executeMotorCommand(root);
  }
}

//gets the distance the lidar detects in inches
//float getLidarInches(){
//  float distance = lidar.getDistance();
//  if( distance < 255 ) {
//    return distance * 0.03937;
//  }
//  else {
//    return 9999;
//  }
//  
//}


void executeMotorCommand(JsonObject& root) {
  int cmd = root["c"];
  switch(cmd) {
    case FORWARD:
      lastCommand = forward;
      if(root.containsKey("timing")) {
        Serial.println("Going Forward With Timing");
        robot.forward(root["p"],root["t"]);
      }
      else {
        Serial.println("Going Forward");
        robot.forward(root["p"]);
      }
      break;
    case BACK:
      lastCommand = back;
      if(root.containsKey("timing")) {
        Serial.println("Going Back With Timing");
        robot.back(root["p"],root["t"]);
      }
      else {
        Serial.println("Going Back");
        robot.back(root["p"]);
      }
      break;
    case LEFT:
      lastCommand = left;
      if(root.containsKey("timing")) {
        Serial.println("Going Left With Timing");
        robot.left(root["p"],root["t"]);
      }
      else {
        Serial.println("Going Left");
        robot.left(root["p"]);
      }
      break;
    case RIGHT:
      lastCommand = right;
      if(root.containsKey("timing")) {
        Serial.println("Going Right With Timing");
        robot.right(root["p"],root["t"]);
      }
      else {
        Serial.println("Going Right");
        robot.right(root["p"]);
      }
      break;
    case STOP:
      lastCommand = stop;
      Serial.println("Stopping");
      robot.stop();
      break;
  }
}



void loop() {
  
  if (Serial.available() > 0) { //&& commandRecieved == false && count++ < 50) {
    buff = Serial.readString();
    parseCommand();
  }
  
//  if(getLidarInches() < 6 && lastCommand == FORWARD) {
//    robot.stop();
//    lastCommand = stop;
//  }
  
}
