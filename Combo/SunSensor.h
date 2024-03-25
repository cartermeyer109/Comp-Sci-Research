//A class to store sunsensors pin vars, data vars,
//and functions. Multiple class instances can be created
//to use multiple sun sensors
class SunSensor {
public:
//DATA MEMBERS
  int sunPin;
  int resetPin;
  int sunVal;
  
//*************************************************************************
//CONSTRUCTORS
  //default constructor
  SunSensor() {
    sunPin = 0;
    sunVal = 0;
    resetPin = 0;
  }
  
  //constructor that sets sunPin and resetPin
  SunSensor(int sp, int rp):sunPin(sp), resetPin(rp){sunVal = 0;}
  
//*************************************************************************
//MEMBER FUNCTIONS
  //To be called in setup
  void initialize() {
    pinMode(resetPin, OUTPUT);
    digitalWrite(resetPin, HIGH);
  }
  
  //Sets all the pins
  void setPins(int sp, int rp) {
    sunPin = sp;
    resetPin = rp;
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

  //Turns reset pin to low after 10 seconds
  void resetDevice(){
    Serial.println("resetting sun sensor");
    delay(10000);
    digitalWrite(resetPin, LOW);
    Serial.println("If you see this it not work");
  }
};
