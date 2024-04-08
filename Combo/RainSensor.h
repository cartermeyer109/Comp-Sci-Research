
//A class to store rain sensors pin vars, data vars,
//and functions. Multiple class instances can be created
//to use multiple rain sensors
class RainSensor {
public:
//DATA MEMBERS
  int rainPin;
  int dropCount;
  bool dropBucketPosition;
  const static double bucketAmount{0.11 * 16.3871}; //inches -> ml
  double minuteRainVol;
  
//*************************************************************************
//CONSTRUCTORS
  //default constructor
  RainSensor() {
    rainPin = 0;
    dropCount = 0;
    dropBucketPosition = true;
    minuteRainVol = 0;
  }
  
  //constructor that sets sunPin and sunPower
  RainSensor(int rp):rainPin(rp){
    dropCount = 0;
    dropBucketPosition = true;
    minuteRainVol = 0;
  }
  
//*************************************************************************
//MEMBER FUNCTIONS
  //To be called in setup
  void initialize() {
    pinMode(RainPin, INPUT_PULLUP);
    Serial.println("Rainfall gauge Ready");
  }
  
  //Sets all the pins
  void setPin(int rp) {
    rainPin = rp;
  }

  //*****TODO \/ \/ \/

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
