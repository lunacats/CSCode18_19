#include <Pixy2.h>
#include <PIDLoop.h>
#include <stdlib.h>

using namespace std;

Pixy2 pixy;
PIDLoop panLoop(400, 0, 400, true);
PIDLoop tiltLoop(500, 0, 500, true);

void setup()
{
  Serial.begin(115200);
  Serial.print("Starting...\n");
 
  // We need to initialize the pixy object 
  pixy.init();
  // Use color connected components program for the pan tilt to track 
  pixy.changeProg("color_connected_components");
}


void loop() {
  // put your main code here, to run repeatedly:
  repeat1();
  repeat2();
  repeat3();
  repeat4();
  repeat5();
}
