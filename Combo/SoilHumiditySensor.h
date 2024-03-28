#include <SHT1x.h>

//A class to store soil humidity vars and
//functions. Multiple class instances can be created
//to use multiple soil humidity sensor
class SoilHumiditySensor {
public:
//DATA MEMBERS
  int dataPin;
  int clockPin;
  float temp_c;
  float temp_f;
  float humidity;
  SHT1x sensor = SHT1x(0, 0);
  
//*************************************************************************
//CONSTRUCTORS
  //default constructor
  SoilHumiditySensor() {
    dataPin = -1;
    clockPin = -1;
    temp_c = -1;
    temp_f = -1;
    humidity = -1;
  }

  SoilHumiditySensor(int dp, int cp):dataPin(dp), clockPin(cp) {
    temp_c = -1;
    temp_f = -1;
    humidity = -1;
    sensor = SHT1x(dataPin, clockPin);
  }
  
//*************************************************************************
//MEMBER FUNCTIONS
  //To be called in setup
  void initialize() {}

  void setPins(int dp, int cp) {
    dataPin = dp;
    clockPin = cp;
    sensor = SHT1x(dataPin, clockPin);
  }
  
  //Returns and prints temperature in celcius
  float readTemperatureCelcius() {
    temp_c = sensor.readTemperatureC();
    Serial.print("Temperature: ");
    Serial.print(temp_c, DEC);
    Serial.print("C.");
  }

  //Returns and prints temperature in fahrenheit
  float readTemperatureFahrenheit() {
    temp_f = sensor.readTemperatureF();
    Serial.print("Temperature: ");
    Serial.print(temp_f, DEC);
    Serial.print("F.");
  }

  //Returns and prints humidity
  float readHumidity() {
    humidity = sensor.readHumidity();
    Serial.print("Humidity: ");
    Serial.print(temp_f, DEC);
    Serial.print(humidity);
    Serial.println("%"); 
  }
};
