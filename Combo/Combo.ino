//Sun Sensor has no includes
#include <Arduino.h>
#include "ComboClasses.h"

//Sun Sensor Object 
SunSensor sun = SunSensor(A0, 12); //(sunPin, resetPin)
  
void setup() {
  //One serial for all devices
  Serial.begin(9600);

  //Initializations
  sun.initialize();
}

void loop() {
  sun.printSunlight();
  delay(1000);
  sun.resetDevice();

}
