//Impliment 30 second timer to send data (impliment loop code)
//Impliment code to deal with if u disconnect from wifi 
// (Compare last time on server to current time) to know what data to send

#include <Arduino.h>
#include "SunSensor.h"
#include "SoilMoisture.h"
#include "Sleep.h"
#include "SDCard.h"
#include "AirHumiditySensor.h"
#include "SoilHumiditySensor.h"
#include "WeatherMeter.h"
#include <DS3231.h>
#include "RainSensor.h"
#include "Wifi.h"
#include "RTClib.h"

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

//WeatherMeterPins (Wind)
int windDirectionPin = 3;
int windSpeedPin = A2; 
int weatherMeterRF = -1; //Needs to exist for the weather meter, but we use other code for the rainfall

//RainfallPins
int rainfallPin = 9;

//WifiPins
int CSPin = 8;
int IRQPin = 7;
int RSTPin = 4;
//Vin:5V
//GND:GND
//SCK/Clock:D52
//MISO/DO:D50
//MOSI/DI:D51
//EN:5V
String ssid = "StoutNonSecure";

//****************************************************************
//OBJECTS

//Sun Sensor Object: TESTED - WORKS
SunSensor sun = SunSensor(sunPin, sunPower);

//Soil Moisture Sensor Object
SoilSensor moisture = SoilSensor(soilPin, soilPower);

//Sleep is a static class
//all functions are used with Sleep::

//Clock is a static class: TESTED - TODO need to get setting normal time to work, and perhaps getters
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
WeatherMeter wind = WeatherMeter(windDirectionPin, windSpeedPin, weatherMeterRF);

//Rainfall Object: TESTED - WORKS on OG code, not tested on combo code
RainSensor rain = RainSensor(rainfallPin);

//WiFi Object: TESTED - WORKS on OG code, not tested on combo code
Wifi wifi = Wifi(ssid, CSPin, IRQPin, RSTPin);

//**********************************************************************************
//MAIN

unsigned long startTime;
int dataInterval = 30; //seconds
  
void setup() {
  //TODO soilhumiditysensor and weather meter use different serial in example??
  //One serial for all devices
  Serial.begin(9600);
  while(!Serial); // wait for Arduino Serial Monitor (native USB boards)

  //Initializations
  //Clock::initialize();
  //memoryCard.initialize();
  //sun.initialize();
  // 
  //rain.initialize();
  //wind.initialize();

  wifi.initialize();
  //moisture.initialize();
  //Sleep::initialize();
  //airHumidity.initialize();


//FINAL CODE++++++++++++++++++++++++++++++++++++++
  
  
  RTC_Millis rtc;
  DateTime now = rtc.now();
  startTime = millis();
//++++++++++++++++++++++++++++++++++++++++++++++++
}

void loop() {
//FINAL CODE++++++++++++++++++++++++++++++++++++++
  rain.checkBucket();

  //Run every 30 seconds
  if (millis() - startTime >= (dataInterval * 1000)) {
    //turn on all other sensors
    sendData();
    //turn all other sensors off
    rain.resetRain();
    startTime = millis();
  }
//++++++++++++++++++++++++++++++++++++++++++++++++



//  wind.readWindDirection();
//  wind.readWindSpeed();
//  delay(1000);

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
