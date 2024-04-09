//TODOImpliment 30 second timer to send data (impliment loop code)
//TODOImpliment code to deal with if u disconnect from wifi 
// (Compare last time on server to current time) to know what data to send
//TODO impliment sleep for each device indiviudall
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
int clockSCL = A5;

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
int windDirectionPin = A3; //TODO these pins should actually be one pin
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

//**Sun Sensor Object
SunSensor sun = SunSensor(sunPin, sunPower);

//++Soil Moisture Sensor Object
SoilSensor moisture = SoilSensor(soilPin, soilPower);

//XXSleep is a static class
//XXall functions are used with Sleep::

//**Clock is a static class
//**all functions are used with Clock::
DS3231  rtc(clockSDA, clockSCL);
#include "Clock.h" //This must be included after rtc because the class uses rtc

//**SD Card Reader Object
SDCard memoryCard = SDCard(chipSelectPin);

//++Air Humidity Sensor Object
AirHumiditySensor airHumidity = AirHumiditySensor();

//XXSoil Humidity Sensor Object
SoilHumiditySensor soilHumidity = SoilHumiditySensor(dataPin, clockPin);

//++Weather Meter Object
WeatherMeter wind = WeatherMeter(windDirectionPin, windSpeedPin, weatherMeterRF);

//++Rainfall Object
RainSensor rain = RainSensor(rainfallPin);

//++WiFi Object
Wifi wifi = Wifi(ssid, CSPin, IRQPin, RSTPin);

//**********************************************************************************
//MAIN

//vairables
unsigned long startTime;
int dataInterval = 30; //seconds
String currentTime = rtc.getDOWStr()+rtc.getDateStr()rtc.getTimeStr();
String wifiTime;
bool wifiConnected;
  
void setup() {
    //One serial for all devices
    Serial.begin(9600);
    while(!Serial); // wait for Arduino Serial Monitor (native USB boards) TODO remove in final code

    //Initializations
    //Clock::initialize();
    //memoryCard.initialize();
    //sun.initialize();
   
    //rain.initialize();
    //wind.initialize();
    //wifi.initialize();
    //moisture.initialize();
    //Sleep::initialize();
    //airHumidity.initialize();


//FINAL CODE++++++++++++++++++++++++++++++++++++++
    startTime = millis();
//++++++++++++++++++++++++++++++++++++++++++++++++
}

void loop() {
//FINAL CODE++++++++++++++++++++++++++++++++++++++
  rain.checkBucket(); //Rain data gathered always

  //Get current time
  currentTime = rtc.getDOWStr()+rtc.getDateStr()rtc.getTimeStr();

  //If wifi is connected
  if (wifi.checkConnection()) {

    //Mark the last time connected to
    //wifi as the current time
    wifiTime = currentTime;

    //If wifi was previously disconnected,
    //consider it connected and sync data to the cloud
    if (!wifiConnected) {
      wifiConnected = true;
      //***resync files
    }
  }
  else if (wifiConnected) {
    wifiConnected = false;
  }

  //Run every 30 seconds
  if (millis() - startTime >= (dataInterval * 1000)) {
    //***turn on all other sensors
    sendData();
    //***turn all other sensors off
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
