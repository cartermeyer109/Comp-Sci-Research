//TODOImpliment code to deal with if u disconnect from wifi 
// (Compare last time on server to current time) to know what data to send
//TODO impliment sleep for each device indiviudally

#include <Arduino.h>
#include "SunSensor.h"
#include "SoilMoisture.h"
#include "Sleep.h"
#include "SDCard.h"
#include "AirHumiditySensor.h"
#include "SoilHumiditySensor.h"
#include <DS3231.h>
#include "RainSensor.h"
#include "Wifi.h"
#include "RTClib.h"
#include "WindSensor.h"

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
int windDirectionPin = A2;
int windSpeedPin = 3; 

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

//WORKS**Sun Sensor Object (NEEDS FUTURE TESTING AFTER NEW WIRING)
SunSensor sun = SunSensor(sunPin, sunPower);

//WORKS**Clock is a static class
//WORKS**all functions are used with Clock::
DS3231  rtc(clockSDA, clockSCL);
#include "Clock.h" //This must be included after rtc because the class uses rtc

//WORKS**SD Card Reader Object
SDCard memoryCard = SDCard(chipSelectPin);

//WORKS**Rainfall Object
RainSensor rain = RainSensor(rainfallPin);

//WORKS** - WindSensor Object
//.h file is just a collection of functions

//FINALTEST++WiFi Object
Wifi wifi = Wifi(ssid, CSPin, IRQPin, RSTPin);

//CURRENTLY NOT WORKING ON MAIN BOARD - Soil Humidity Sensor Object
SoilHumiditySensor soilHumidity = SoilHumiditySensor(dataPin, clockPin);

//REDO FEMALE CONNECTION (KEEPS PRINTING 1023) - Soil Moisture Sensor Object
SoilSensor moisture = SoilSensor(soilPin, soilPower);

//REDO WIRE CONNECTION - Air Humidity Sensor Object
AirHumiditySensor airHumidity = AirHumiditySensor();

//NOT TESTEDxxSleep is a static class
//NOT TESTEDxxall functions are used with Sleep::
//NEEDS REVAMPING, ALSO IS INDEPENDANT OF BOARD 

//**********************************************************************************
//MAIN

//vairables
unsigned long startTime;
int dataInterval = 5; //seconds
String currentTime;
String wifiTime;
bool wifiConnected;
  
void setup() {
    //One serial for all devices
    Serial.begin(9600);
    while(!Serial); // wait for Arduino Serial Monitor (native USB boards) TODO remove in final code

    //INITIALIZATIONS
    //**WORKING
    //Clock::initialize();
    //memoryCard.initialize();
    //sun.initialize();
    //rain.initialize();
    //windInitialize();

    //**UNTESTED
    //soilHumidity.initialize();
    //wifi.initialize();
    //Sleep::initialize();

    //**NOT WORKING
    //airHumidity.initialize();
    //moisture.initialize();
                         

//FINAL CODE++++++++++++++++++++++++++++++++++++++
//    currentTime = String(rtc.getDOWStr())+" " 
//                  + String(rtc.getDateStr())+" "
//                  + String(rtc.getTimeStr());
//    startTime = millis();
//++++++++++++++++++++++++++++++++++++++++++++++++
}

void loop() {
  
//FINAL CODE++++++++++++++++++++++++++++++++++++++
//  rain.checkBucket(); //Rain data gathered always
//
//  //Get current time
//  currentTime = String(rtc.getDOWStr())+" " 
//                + String(rtc.getDateStr())+" "
//                + String(rtc.getTimeStr());//
//
//  //If wifi is connected
//  if (wifi.checkConnection()) {
//
//    //Mark the last time connected to
//    //wifi as the current time
//    wifiTime = currentTime;
//
//    //If wifi was previously disconnected,
//    //consider it connected and sync data to the cloud
//    if (!wifiConnected) {
//      wifiConnected = true;
//      //***resync files
//    }
//  }
//  else if (wifiConnected) {
//    wifiConnected = false;
//  }
//
//  //Run every 30 seconds
//  if (millis() - startTime >= (dataInterval * 1000)) {
//    //***turn on all other sensors
//    //sendData();
//    //***turn all other sensors off
//    rain.resetRain();
//    startTime = millis();
//  }
//++++++++++++++++++++++++++++++++++++++++++++++++


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
//TODO figure out how we want to do setting device high and low (seperate functions or within the read functions)
String sendData() {
    String data = String(sun.readSunlight()) + "/" +
                String(airHumidity.readTemperature()) + "/" +
                String(airHumidity.readHumidity()) + "/" +
                String(soilHumidity.readTemperatureFahrenheit()) + "/" +
                String(soilHumidity.readHumidity());
    return data;
}
