#include <DS3231.h>

Time t;

//A class to store clock pin vars
//and functions.
class Clock {
public:
//MEMBER FUNCTIONS
  //To be called in setup
  static void initialize() {
    rtc.begin();
  }
  
  //Prints the current time
  static void printDateTime() {
    Serial.print("Current Time.............................: ");
    Serial.print(rtc.getDOWStr());
    Serial.print(" ");
    Serial.print(rtc.getDateStr());
    Serial.print(" -- ");
    Serial.println(rtc.getTimeStr());
  }

  //Prints the current unix time
  static void printUnixDateTime(){
    Serial.print("Current Unixtime.........................: ");
    Serial.println(rtc.getUnixTime(rtc.getTime()));
  }

  //Sets hour, minutes, and seconds
  static void setTime(int h, int m, int s) {
    t.hour = h;
    t.min = m;
    t.sec = s;
  }

  //sets year, month, day
  static void setDate(int y, int m, int d) {
    t.year = y;
    //rtc.setYear(y);
    t.mon = m;
    //rtc.setMonth(m);
    t.date = d;
    //rtc.setDate(d);
  }
};

//PIN DIRECTIONS***********************************************************
// To use the hardware I2C (TWI) interface of the Arduino you must connect
// the pins as follows:
//
// Arduino Uno/2009:
// ----------------------
// DS3231:  SDA pin   -> Arduino Analog 4 or the dedicated SDA pin
//          SCL pin   -> Arduino Analog 5 or the dedicated SCL pin
//
// Arduino Leonardo:
// ----------------------
// DS3231:  SDA pin   -> Arduino Digital 2 or the dedicated SDA pin
//          SCL pin   -> Arduino Digital 3 or the dedicated SCL pin
//
// Arduino Mega:
// ----------------------
// DS3231:  SDA pin   -> Arduino Digital 20 (SDA) or the dedicated SDA pin
//          SCL pin   -> Arduino Digital 21 (SCL) or the dedicated SCL pin
//
// Arduino Due:
// ----------------------
// DS3231:  SDA pin   -> Arduino Digital 20 (SDA) or the dedicated SDA1 (Digital 70) pin
//          SCL pin   -> Arduino Digital 21 (SCL) or the dedicated SCL1 (Digital 71) pin
//
// The internal pull-up resistors will be activated when using the 
// hardware I2C interfaces.
//
// You can connect the DS3231 to any available pin but if you use any
// other than what is described above the library will fall back to
// a software-based, TWI-like protocol which will require exclusive access 
// to the pins used, and you will also have to use appropriate, external
// pull-up resistors on the data and clock signals.
