#include <Adafruit_SleepyDog.h>

//A class for making a device fall asleep, currently sends whole board to sleep
class Sleep {
public:
//DATA MEMBERS
  static int prevSleepTime;
  
//*************************************************************************
//MEMBER FUNCTIONS
  //To be called in setup
  static void initialize() {
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH); // Show we're awake
  }
  
  //Goes to sleep for as long as possible
  static int goToSleep() {
    Serial.println("Going to sleep in one second...");
    delay(1000);
    // To enter low power sleep mode call Watchdog.sleep() like below
    // and the watchdog will allow low power sleep for as long as possible.
    // The actual amount of time spent in sleep will be returned (in 
    // milliseconds).
    digitalWrite(LED_BUILTIN, LOW); // Show we're asleep
    int prevSleepTime = Watchdog.sleep();
    return prevSleepTime;
  }

  //goes to sleep for a set amount of time
  static int goToSleep(int ms) {
    Serial.println("Going to sleep in one second...");
    delay(1000);
    // To enter low power sleep mode call Watchdog.sleep() like below
    // and the watchdog will allow low power sleep for as long as possible.
    // The actual amount of time spent in sleep will be returned (in 
    // milliseconds).
    digitalWrite(LED_BUILTIN, LOW); // Show we're asleep
    int prevSleepTime = Watchdog.sleep(ms);
    return prevSleepTime;
  }

  //reconnects device and proves that it is awake
  //THIS SHOULD BE CALLED RIGHT AFTER A SLEEP FUNCTION
  static void wakeUp(){
    digitalWrite(LED_BUILTIN, HIGH); // Show we're awake again
    // Try to reattach USB connection on "native USB" boards (connection is
    // lost on sleep). Host will also need to reattach to the Serial monitor.
    // Seems not entirely reliable, hence the LED indicator fallback.
    #if defined(USBCON) && !defined(USE_TINYUSB)
      USBDevice.attach();
    #endif
    Serial.print("I'm awake now! I slept for ");
    Serial.print(prevSleepTime, DEC);
    Serial.println(" milliseconds.");
    Serial.println();
  }
};

int Sleep::prevSleepTime = 0;
