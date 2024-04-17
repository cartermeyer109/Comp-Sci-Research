//TODOImpliment 30 second timer to send data (impliment loop code)
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
//#include "WindSensor.h"

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
int windDirectionPin = A2; //TODO these pins should actually be one pin
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

//FINALTEST++WiFi Object
Wifi wifi = Wifi(ssid, CSPin, IRQPin, RSTPin);

//CURRENTLY NOT WORKING ON MAIN BOARD - Soil Humidity Sensor Object
SoilHumiditySensor soilHumidity = SoilHumiditySensor(dataPin, clockPin);

//REDO FEMALE CONNECTION (KEEPS PRINTING 1023) - Soil Moisture Sensor Object
SoilSensor moisture = SoilSensor(soilPin, soilPower);

//REDO WIRE CONNECTION - Air Humidity Sensor Object
AirHumiditySensor airHumidity = AirHumiditySensor();

//MY CODE IS FAULTY - WindSensor Object
WindSensor wind = WindSensor(windDirectionPin, windSpeedPin);

//NOT TESTEDxxSleep is a static class
//NOT TESTEDxxall functions are used with Sleep::
//NEEDS REVAMPING

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
long lastSecond; //The millis counter to see when a second rolls by
byte seconds; //When it hits 60, increase the current minute
byte seconds_2m; //Keeps track of the "wind speed/dir avg" over last 2 minutes array of data
byte minutes; //Keeps track of where we are in various arrays of data
byte minutes_10m; //Keeps track of where we are in wind gust/dir over last 10 minutes array of data
long lastWindCheck = 0;
volatile long lastWindIRQ = 0;
volatile byte windClicks = 0;
byte windspdavg[120]; //120 bytes to keep track of 2 minute average
#define WIND_DIR_AVG_SIZE 120
int winddiravg[WIND_DIR_AVG_SIZE]; //120 ints to keep track of 2 minute average
float windgust_10m[10]; //10 floats to keep track of 10 minute max
int windgustdirection_10m[10]; //10 ints to keep track of 10 minute max
volatile float rainHour[60]; //60 floating numbers to keep track of 60 minutes of rain


//These are all the weather values that wunderground expects:
int winddir = 0; // [0-360 instantaneous wind direction]
float windspeedmph = 0; // [mph instantaneous wind speed]
float windgustmph = 0; // [mph current wind gust, using software specific time period]
int windgustdir = 0; // [0-360 using software specific time period]
float windspdmph_avg2m = 0; // [mph 2 minute average wind speed mph]
int winddir_avg2m = 0; // [0-360 2 minute average wind direction]
float windgustmph_10m = 0; // [mph past 10 minutes wind gust mph ]
int windgustdir_10m = 0; // [0-360 past 10 minutes wind gust direction]


void wspeedIRQ()
// Activated by the magnet in the anemometer (2 ticks per rotation), attached to input D3
{
    if (millis() - lastWindIRQ > 10) // Ignore switch-bounce glitches less than 10ms (142MPH max reading) after the reed switch closes
    {
        lastWindIRQ = millis(); //Grab the current time
        windClicks++; //There is 1.492MPH for each click per second.
    }
}

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



  //Initialize serial and wait for port to open:
  Serial.begin(9600);

   pinMode(WSPEED, INPUT_PULLUP); // input from wind meters windspeed sensor
 
   
    seconds = 0;
    lastSecond = millis();

    // attach external interrupt pins to IRQ functions
  
    attachInterrupt(1, wspeedIRQ, FALLING);
    // turn on interrupts
    interrupts();
    Serial.println("Weather Shield online!");
    
    //INITIALIZATIONS
    //**WORKING
    //Clock::initialize();
    //memoryCard.initialize();
    //sun.initialize();
    //rain.initialize();

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
  // put your main code here, to run repeatedly:
  current_wind_speed();
  winddir=get_wind_direction();
  Serial.println(winddir);
  delay(2000);
  
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
//
//float current_wind_speed()
//{
//    float deltaTime = millis() - lastWindCheck;    //750ms
//
//    deltaTime /= 1000.0; //Convert to seconds
//
//    float windSpeed = (float)windClicks / deltaTime; //3 / 0.750s = 4
//
//    windClicks = 0; //Reset and start watching for new wind
//    lastWindCheck = millis();
//
//    windSpeed *= 1.492; //4 * 1.492 = 5.968MPH
//    windspeedmph=0.0;
//    windspeedmph=windSpeed;
//
//    Serial.print("\nWind Speed mph: ");
//    Serial.println(windspeedmph);
//}
//
////Read the wind direction sensor, return heading in degrees
//int get_wind_direction()
//{
//    unsigned int adc;
//    adc = analogRead(WDIR); // get the current reading from the sensor
//    // The following table is ADC readings for the wind direction sensor output, sorted from low to high.
//    // Each threshold is the midpoint between adjacent headings. The output is degrees for that ADC reading.
//    // Note that these are not in compass degree order! See Weather Meters datasheet for more information.
//
//    if (adc < 380) return (113);
//    if (adc < 393) return (68);
//    if (adc < 414) return (90);
//    if (adc < 456) return (158);
//    if (adc < 508) return (135);
//    if (adc < 551) return (203);
//    if (adc < 615) return (180);
//    if (adc < 680) return (23);
//    if (adc < 746) return (45);
//    if (adc < 801) return (248);
//    if (adc < 833) return (225);
//    if (adc < 878) return (338);
//    if (adc < 913) return (0);
//    if (adc < 940) return (293);
//    if (adc < 967) return (315);
//    if (adc < 990) return (270);
//    return (-1); // error, disconnected?
//}
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
