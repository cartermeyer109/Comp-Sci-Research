//A class to store sunsensors pin vars, data vars,
//and functions. Multiple class instances can be created
//to use multiple sun sensors
class SunSensor {
public:
//DATA MEMBERS
  int sunPin;
  int sunPower;
  int sunVal;
  
//*************************************************************************
//CONSTRUCTORS
  //default constructor
  SunSensor() {
    sunPin = 0;
    sunVal = 0;
    sunPower = 0;
  }
  
  //constructor that sets sunPin and sunPower
  SunSensor(int sp, int rp):sunPin(sp), sunPower(rp){sunVal = 0;}
  
//*************************************************************************
//MEMBER FUNCTIONS
  //To be called in setup
  void initialize() {
    pinMode(sunPower, OUTPUT);
    digitalWrite(sunPower, HIGH);
  }
  
  //Sets all the pins
  void setPins(int sp, int rp) {
    sunPin = sp;
    sunPower = rp;
  }

  //Instantly returns the sunlight value being gathered
  //by the sun sensor after printing it to serial
  int readSunlight(){
    sunVal = analogRead(sunPin);
    Serial.print("Sunlight Level: ");
    Serial.println(sunVal);
    //delay(1000);
    return sunVal;
  }

  //Turns reset pin to low after 10 seconds, to be implimented later on all devices
  void setLow(){
    Serial.println("resetting sun sensor");
    //delay(10000); //10 seconds
    digitalWrite(sunPower, LOW);
    Serial.println("sun sensor did not reset");
  }
};
