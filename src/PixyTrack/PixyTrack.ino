#include <Pixy2.h>
#define MAX_X 320
#define MAX_Y 200
#define DEBUG 1

Pixy2 pixy;
int16_t servoPos[2];

void setup() {
  // put your setup code here, to run once:
  if(DEBUG) Serial.begin(9600);
  servoPos[0] = 500; servoPos[1] = 500;
  pixy.init();
  pixy.setServos(servoPos[0], servoPos[1]);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint16_t blockCount = pixy.ccc.getBlocks();
  if(DEBUG) Serial.println(blockCount);
  uint16_t maxAge = 0;
  for(uint16_t i = 0; i < blockCount; i++){
    if(DEBUG) pixy.ccc.blocks[i].print();
    if(pixy.ccc.blocks[i].m_age > pixy.ccc.blocks[maxAge].m_age){
      maxAge = i;
    }
  }
  if(blockCount == 0)
    return;
  
  servoPos[0] += pixy.ccc.blocks[maxAge].m_x - MAX_X/2;
  servoPos[1] += pixy.ccc.blocks[maxAge].m_y - MAX_Y/2;
  servoPos[0] = max(0, min(servoPos[0], 1000));
  servoPos[1] = max(0, min(servoPos[1], 1000));
  pixy.setServos(1000 - (uint16_t)servoPos[0], (uint16_t)servoPos[1]);
}
