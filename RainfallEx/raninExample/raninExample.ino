#include <Wire.h> //I2C needed for sensors
#include <Adafruit_GPS.h>
#include <Arduino.h>
#include "Adafruit_SHT31.h"
#include <SHT1x.h>
#include "RTClib.h"
#include "DS3231.h"

//WiFi Libaries
#include <SPI.h>
#include <avr/wdt.h>
#include <SD.h>

// ++++++++++++++++++ Rainfall declarations ++++++++++++++++++
#define RainPin 9                         // The Rain input is connected to digital pin 2 on the arduino

int count=0;
bool bucketPositionA = false;             // one of the two positions of tipping-bucket               
const double bucketAmount = 0.011 * 16.3871;  //0.01610595;   // inches equivalent of ml to trip tipping-bucket
double dailyRain_in_15_Second = 0.0;  // rain accumulated for the day
double minuteRain=0.0;
RTC_Millis rtc;                           // software RTC time
DateTime now = rtc.now(); 
// ++++++++++++++++++ End of Rainfall declerations ++++++++++++++++++
void setup()
{
  bucketPositionA = true;
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(RainPin, INPUT_PULLUP);                       // set the Rain Pin as input.
  delay(100);                                   // i'm slow in starting the seiral monitor (not necessary)
  Serial.println("Rainfall gague Ready!!!");
  count=0;
}

void loop() {
  // put your main code here, to run repeatedly:
rainFall_function();
//Serial.println(digitalRead(RainPin));
}
void rainFall_function()
{
  DateTime now = rtc.now(); 
    //count=0;
  dailyRain_in_15_Second=0;
   unsigned long startedAt = millis();
  
   do
   {
                
      // ++++++++++++++++++++++++ Count the bucket tips ++++++++++++++++++++++++++++++++
     if ((bucketPositionA==false)&&(digitalRead(RainPin)==HIGH)){
      bucketPositionA=true;
      dailyRain_in_15_Second+=bucketAmount;     // update the daily rain
      count=count+1;
      Serial.println("I am HIGH");
   
      }
  
    if ((bucketPositionA==true)&&(digitalRead(RainPin)==LOW)){
       bucketPositionA=false;  
        Serial.println("I am LOW");
     } 
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    
  
   }
          //current time - beginning time < 5 seconds
   while(millis() - startedAt <5000); //while time < 5 seconds
   
   Serial.print("\nReading data at second: ");
   Serial.println(now.second());
   
   Serial.print("bucketAmount:");
   Serial.println(count);

   Serial.print("RainAmount in 5 second: ");    
   Serial.print(dailyRain_in_15_Second,8);
   Serial.println(" ml");

//    Serial.print("RainAmount minute second: ");   
//    minuteRain= dailyRain_in_15_Second;
//   Serial.print(minuteRain,8);
//   Serial.println(" ml");

   
}
