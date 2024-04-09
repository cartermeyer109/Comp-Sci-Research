//A class to store rain sensors pin vars, data vars,
//and functions. Multiple class instances can be created
//to use multiple rain sensors
class RainSensor {
public:
//DATA MEMBERS
  int rainPin;
  int dropCount;
  bool dropBucketPosition;
  static constexpr double bucketAmount{0.11 * 16.3871}; //inches -> ml
  double rainAmount; //ml
  
//*************************************************************************
//CONSTRUCTORS
  //default constructor
  RainSensor() {
    rainPin = 0;
    dropCount = 0;
    dropBucketPosition = true;
    rainAmount = 0;
  }
  
  //constructor that sets pins
  RainSensor(int rp):rainPin(rp){
    dropCount = 0;
    dropBucketPosition = true;
    rainAmount = 0;
  }
  
//*************************************************************************
//MEMBER FUNCTIONS
  //To be called in setup
  void initialize() {
    pinMode(rainPin, INPUT_PULLUP);
    Serial.println("Rainfall gauge Ready");
  }
  
  //Sets all the pins
  void setPin(int rp) {
    rainPin = rp;
  }

  //Adds or does not add the bucketamount to the rain value
  int checkBucket(){
     if ((dropBucketPosition==false)&&(digitalRead(rainPin)==HIGH)){
      dropBucketPosition=true;
      rainAmount += bucketAmount;  // update the total rain
      dropCount++;
      Serial.println("I am tipped");
   
     }
  
    if ((dropBucketPosition==true)&&(digitalRead(rainPin)==LOW)){
       dropBucketPosition=false;  
        Serial.println("I am NOT tipped");
    } 
  }

  void resetRain() {
    rainAmount = 0;
  }
};
