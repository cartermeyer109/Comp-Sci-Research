#include <Arduino.h>
#include "SunSensor.h"
#include "SoilMoisture.h"
#include "Sleep.h"
#include "Clock.h"
#include "SDCard.h"
#include "AirHumiditySensor.h"
#include "SoilHumiditySensor.h"

//*****************************************************************
// PINS

//SunSensorPins
int sunPin = A0;
int sunPower = 12;

//SoilMoisturePins
int soilPin = A1;
int soilPower = 52;

//SDCardPins
int chipSelectPin = 53;

//SoilHumidityTempPins
int dataPin = 10;
int clockPin = 11;

//****************************************************************
//OBJECTS

//Sun Sensor Object 
SunSensor sun = SunSensor(sunPin, sunPower);

//Soil Moisture Sensor Object
SoilSensor moisture = SoilSensor(soilPin, soilPower);

//Sleep is a static class

//Clock is a static class

//SD Card Reader Object
SDCard memoryCard = SDCard(chipSelectPin);

//Air Humidity Sensor Object
AirHumiditySensor airHumidity = AirHumiditySensor();

//Soil Humidity Sensor Object
SoilHumiditySensor soilHumidity = SoilHumiditySensor(dataPin, clockPin);

//**********************************************************************************
//MAIN
  
void setup() {
  //TODO soilhumiditysensor uses different serial in example??
  //One serial for all devices
  Serial.begin(9600);
  while(!Serial); // wait for Arduino Serial Monitor (native USB boards)

  //Initializations
  sun.initialize();
  moisture.initialize();
  Sleep::initialize();
  Clock::initialize();
  memoryCard.initialize();
  airHumidity.initialize();
}

void loop() {
  //Sun Sensor Loop
  sun.readSunlight();
  delay(1000);
  sun.setLow();

  //Soil Moisture Loop
  moisture.readMoisture();

  //Air Humidity Loop
  airHumidity.readTemperature();
  airHumidity.readHumidity();

  //WARNING this is based on number of times
  //the loop function has been called.
  //could be a good idea to alter it to be
  //based on time.
  //if (airHumidity.loopCnt >= 30) {
  //  airHumidity.switchHeater();
  //}
  airHumidity.loopCnt++;

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

  //sendData();
}

//*****************************************************************************
//MAIN FUNCTIONS

//TODO would send a string of data to somewhere
String sendData() {
  String data = String(sun.readSunlight()) + "/" +
                String(airHumidity.readTemperature()) + "/" +
                String(airHumidity.readHumidity()) + "/" +
                String(soilHumidity.readTemperatureFahrenheit()) + "/" +
                String(soilHumidity.readHumidity());
  return data;
}
