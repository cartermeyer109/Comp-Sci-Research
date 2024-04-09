//A class to store soil moisture pin vars, data vars,
//and functions. Multiple class instances can be created
//to use multiple moisture sensors
class SoilSensor {
public:
//DATA MEMBERS
  int soilPin;
  int soilPower;
  int moistureVal;
  
//*************************************************************************
//CONSTRUCTORS
  //default constructor
  SoilSensor() {
    soilPin = 0;
    soilPower = 0;
    moistureVal = 0;
  }
  
  //constructor that sets sunPin and resetPin
  SoilSensor(int spi, int spo):soilPin(spi), soilPower(spo){
    moistureVal = 0;
  }
  
//*************************************************************************
//MEMBER FUNCTIONS
  //To be called in setup
  void initialize() {
    pinMode(soilPower, OUTPUT);//Sets an OUTPUT
    digitalWrite(soilPower, LOW);//Set to LOW so no power is flowing through the sensor
  }
  
  //Sets all the pins
  void setPins(int spi, int spo) {
    soilPin = spi;
    soilPower = spo;
  }

  //Returns the moisture value being gathered
  //by the soil sensor after printing it to serial
  int readMoisture(){
    Serial.print("Soil Moisture = ");
    digitalWrite(soilPower, HIGH);//turn "On"
    delay(10);//wait 10 milliseconds 
    moistureVal = analogRead(soilPin);//Read the SIG value form sensor 
    digitalWrite(soilPower, LOW);//turn "Off"
    Serial.print(moistureVal);
    return moistureVal;//send current moisture value
  }

};
