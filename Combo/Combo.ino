//Sun Sensor has no includes
#include <Arduino.h>
#include "SunSensor.h"
#include "SoilMoisture.h"
#include "Sleep.h"
#include "Clock.h"
#include "SDCard.h"
#include "HumiditySensor.h"

//Sun Sensor Object 
SunSensor sun = SunSensor(A0, 12); //(sunPin, resetPin)

//Soil Moisture Sensor Object
SoilSensor moisture = SoilSensor(A1, 52); //(soilPin, soilPower)

//Sleep is a static class

//Clock is a static class

//SD Card Reader Object
SDCard memoryCard = SDCard(53); //(chipSelectPin)

//Humidity Sensor Object
HumiditySensor humidity = HumiditySensor();
  
void setup() {
  //One serial for all devices
  Serial.begin(9600);
  while(!Serial); // wait for Arduino Serial Monitor (native USB boards)

  //Initializations
  sun.initialize();
  moisture.initialize();
  Sleep::initialize();
  Clock::initialize();
  memoryCard.initialize();
  humidity.initialize();
}

void loop() {
  //Sun Sensor Loop
  sun.readSunlight();
  delay(1000);
  sun.resetDevice();

  //Soil Moisture Loop
  moisture.readMoisture();

  //Humidity Loop
  humidity.readTemperature();
  humidity.readHumidity();

  //WARNING this is based on number of times
  //the loop function has been called.
  //could be a good idea to alter it to be
  //based on time.
  //if (humidity.loopCnt >= 30) {
  //  humidity.switchHeater();
  //}
  humidity.loopCnt++;

  //Clock Loop
  Clock::printDateTime();
  Clock::printUnixDateTime();

  //SDCard Loop
  //WARNING: will create files if they don't
  //already exist
  //memoryCard.writeToFile("test.txt", "Hello");
  //memoryCard.readFile("test.txt");
  
  //Sleep Test
  Sleep::goToSleep(10000);
  Sleep::wakeUp();
}
