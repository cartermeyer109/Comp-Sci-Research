//TODO, impliment wifi
//TODO impliment rainfall as its own class,
//then remove rainfall related stuff from weather kit

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
int windDirectionPin = 3;
int windSpeedPin = A2; 
int rainfallPin = 9;

//****************************************************************
//OBJECTS

//Sun Sensor Object: TESTED - WORKS
SunSensor sun = SunSensor(sunPin, sunPower);

//Soil Moisture Sensor Object
SoilSensor moisture = SoilSensor(soilPin, soilPower);

//Sleep is a static class
//all functions are used with Sleep::

//Clock is a static class: TESTED - TODO need to get setting normal time to work
//all functions are used with Clock::
DS3231  rtc(clockSDA, clockSDL);
#include "Clock.h" //This must be included after rtc because the class uses rtc

//SD Card Reader Object: TESTED - WORKS
SDCard memoryCard = SDCard(chipSelectPin);

//Air Humidity Sensor Object
AirHumiditySensor airHumidity = AirHumiditySensor();

//Soil Humidity Sensor Object
SoilHumiditySensor soilHumidity = SoilHumiditySensor(dataPin, clockPin);

//Weather Meter Object
WeatherMeter weather = WeatherMeter(windDirectionPin, windSpeedPin, rainfallPin);

//TODO Wifi sheild currently not working with one of the boards

//**********************************************************************************
//MAIN
  
void setup() {
  //TODO soilhumiditysensor and weather meter use different serial in example??
  //One serial for all devices
  Serial.begin(9600);
  while(!Serial); // wait for Arduino Serial Monitor (native USB boards)

  //Initializations
  //Clock::initialize();
  //memoryCard.initialize();
  //sun.initialize();
  weather.initialize();

  //moisture.initialize();
  //Sleep::initialize();
  //airHumidity.initialize();
}

void loop() {
//Clock TEST
  //Clock::printDateTime();
  //Clock::printUnixDateTime();

//Memory Card TEST is the initialization

//Sun Sensor TEST
  //sun.readSunlight();

  //weather.readWindDirection();
  //weather.readWindSpeed();
  weather.readRainfall();
  delay(1000);

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
