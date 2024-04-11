#include "Arduino.h"

//A class to store Wind Sensor's pin vars and functions.
//This class needed a cpp file to properly implement the interrupts

class WindSensor {
public:
//DATA MEMBERS
     int windDirectionPin;
     int windSpeedPin;
     float windDirection;
     float windSpeed;
     float windSpeedMPH;
     volatile long lastWindIRQ;
     volatile byte windClicks;
     long lastWindCheck;

//*************************************************************************
//CONSTRUCTORS
  //default constructor
  WindSensor();
  
  WindSensor(int wdp, int wsp);
//*************************************************************************
//MEMBER FUNCTIONS
     void wspeedIRQ();

     void setPins(int wdp, int wsp);
    
    //to be called in setup
     void initialize();
    
    //prints and returns wind direction
     int readWindDirection();

    //prints and returns wind speed
     int readWindSpeedMPH();
};
