#include <Wire.h>
#include "Adafruit_SHT31.h"

//A class to store humidity vars and
//functions. Multiple class instances can be created
//to use SD cards/readers
class HumiditySensor {
public:
//DATA MEMBERS
  bool enableHeater;
  uint8_t loopCnt = 0;
  Adafruit_SHT31 sht31 = Adafruit_SHT31();
  
//*************************************************************************
//CONSTRUCTORS
  //default constructor
  HumiditySensor() {}
  
//*************************************************************************
//MEMBER FUNCTIONS
  //To be called in setup
  void initialize() {
    Serial.println("SHT31 test");
    if (! sht31.begin(0x44)) {   // Set to 0x45 for alternate i2c addr
      Serial.println("Couldn't find SHT31");
      while (1) delay(1);
    }
    else {
      Serial.println("Humidity Tester Initialized");
    }
  
    Serial.print("Heater Enabled State: ");
    if (sht31.isHeaterEnabled()) {
      Serial.println("ENABLED");
    }
    else {
      Serial.println("DISABLED"); 
    }
  }

  //Returns and prints temperature
  float readTemperature() {
    float t = sht31.readTemperature();
  
    if (! isnan(t)) {  // check if 'is not a number'
      Serial.print("Temp *C = "); Serial.print(t); Serial.print("\t\t");
      return t;
    }
    else { 
      Serial.println("Failed to read temperature");
    }
    return 0;
  }

  //Returns and prints humidity
  float readHumidity() {
    float h = sht31.readHumidity();
    
    if (! isnan(h)) {  // check if 'is not a number'
      Serial.print("Hum. % = "); Serial.println(h);
      return h;
    } 
    else { 
      Serial.println("Failed to read humidity");
    }
    return 0;
  }

  //Switches the heaters
  void switchHeater() {
    if (enableHeater) {
      heaterOff();
    }
    else {
      heaterOn();
    }
  }

  //Turns the heater on and prints status
  void heaterOn() {
    enableHeater = true;
    sht31.heater(enableHeater);
    Serial.print("Heater Enabled State: ");
    if (sht31.isHeaterEnabled())
      Serial.println("ENABLED");
    else
      Serial.println("DISABLED");
  }

  //Turns the heater off and prints status
  void heaterOff() {
    enableHeater = false;
    sht31.heater(enableHeater);
    Serial.print("Heater Enabled State: ");
    if (sht31.isHeaterEnabled())
      Serial.println("ENABLED");
    else
      Serial.println("DISABLED");
  }
  
};
