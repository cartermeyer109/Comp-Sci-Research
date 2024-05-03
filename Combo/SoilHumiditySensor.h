#include <Sensirion.h>

//A class to store soil humidity vars and
//functions. Multiple class instances can be created
//to use multiple soil humidity sensor
class SoilHumiditySensor {
public:
//DATA MEMBERS
  int dataPin;
  int clockPin;
  float temperature;
  float humidity;
  float dewpoint;
  Sensirion tempSensor = Sensirion(0, 0);  
//*************************************************************************
//CONSTRUCTORS
  //default constructor
  SoilHumiditySensor() {
    dataPin = -1;
    clockPin = -1;
    temperature = -1;
    humidity = -1;
    dewpoint = -1;
  }

  SoilHumiditySensor(int dp, int cp):dataPin(dp), clockPin(cp) {
    temperature = -1;
    humidity = -1;
    dewpoint = -1;
    tempSensor = Sensirion(dataPin, clockPin);
  }
  
//*************************************************************************
//MEMBER FUNCTIONS
  //To be called in setup
  void initialize() {}

  void setPins(int dp, int cp) {
    dataPin = dp;
    clockPin = cp;
    tempSensor = Sensirion(dataPin, clockPin);
  }
  
  //Returns and prints temperature in celcius
  float readTemperatureCelcius() {
    tempSensor.measure(&temperature, &humidity, &dewpoint);
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");
    return temperature;
  }

  //Returns and prints humidity
  float readHumidity() {
    tempSensor.measure(&temperature, &humidity, &dewpoint);
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
    return humidity;
  }

  float readDewpoint() {
    tempSensor.measure(&temperature, &humidity, &dewpoint);
    Serial.print("Dewpoint: ");
    Serial.print(dewpoint);
    Serial.println(" C");
    return dewpoint;
  }

};
