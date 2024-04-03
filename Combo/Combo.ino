//TODO Figure out how to set time
#include <Arduino.h>
#include "SunSensor.h"
#include "SoilMoisture.h"
#include "Sleep.h"
#include "SDCard.h"
#include "AirHumiditySensor.h"
#include "SoilHumiditySensor.h"
#include "WeatherMeter.h"
#include <DS3231.h>

//*****************************************************************
//PINS
//ClockPins
int clockSDA = A4;
int clockSDL = A5;

//SunSensorPins
int sunPin = A0;
int sunPower = 12;

//SoilMoisturePins
int soilPin = A1;
int soilPower = 6;

//SDCardPins
int chipSelectPin = 53;
//VCC: 5V
//GND: GND
//MISO/DO:50
//MOSI/DI:51
//SCK/Clock:52
//CS/SS:53

//SoilHumidityTempPins
int dataPin = 10;
int clockPin = 11;

//WeatherMeterPins
//TODO: board only has 2 pins used, but the code requires 3 pins
int windDirectionPin = 3;
int windSpeedPin = -1; //Unkown if this pin is needed
int rainfallPin = 9;

//****************************************************************
//OBJECTS

//Sun Sensor Object 
SunSensor sun = SunSensor(sunPin, sunPower);

//Soil Moisture Sensor Object
SoilSensor moisture = SoilSensor(soilPin, soilPower);

//Sleep is a static class

//Clock is a static class
//all functions are used with Clock::
DS3231  rtc(clockSDA, clockSDL);
#include "Clock.h" //This must be included after rtc because the class uses rtc

//SD Card Reader Object
SDCard memoryCard = SDCard(chipSelectPin);

//Air Humidity Sensor Object
AirHumiditySensor airHumidity = AirHumiditySensor();

//Soil Humidity Sensor Object
SoilHumiditySensor soilHumidity = SoilHumiditySensor(dataPin, clockPin);

WeatherMeter weather = WeatherMeter(windDirectionPin, windSpeedPin, rainfallPin);

//**********************************************************************************
//MAIN
  
void setup() {
  //TODO soilhumiditysensor and weather meter use different serial in example??
  //One serial for all devices
  Serial.begin(9600);
  while(!Serial); // wait for Arduino Serial Monitor (native USB boards)

  //Initializations
  //sun.initialize();
  //moisture.initialize();
  //Sleep::initialize();
  Clock::initialize();
  
  //Clock::setDate(24, 4, 2);
  //Clock::setTime(14, 31, 30);
  //memoryCard.initialize();
  //airHumidity.initialize();
  //weather.initialize();
}

void loop() {
//  //Sun Sensor Loop
//  sun.readSunlight();
//  delay(1000);
//  sun.setLow();
//
//  //Soil Moisture Loop
//  moisture.readMoisture();
//
//  //Air Humidity Loop
//  airHumidity.readTemperature();
//  airHumidity.readHumidity();
//
//  //WARNING this is based on number of times
//  //the loop function has been called.
//  //could be a good idea to alter it to be
//  //based on time.
//  //if (airHumidity.loopCnt >= 30) {
//  //  airHumidity.switchHeater();
//  //}
//  airHumidity.loopCnt++;

  //Clock Loop
  Clock::printDateTime();
  Clock::printUnixDateTime();

//  //SDCard Loop
//  //WARNING: will create files if they don't
//  //already exist
//  //memoryCard.writeToFile("test.txt", "Hello");
//  //memoryCard.readFile("test.txt");
//  
//  //Sleep Test
//  Sleep::goToSleep(10000);
//  Sleep::wakeUp();

  //sendData();
  delay(1000);
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
