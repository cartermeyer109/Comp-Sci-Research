#include "WindSensor.h"

//Default Constructor
WindSensor::WindSensor(){
   windDirectionPin = 0;
   windSpeedPin = 0;
   windDirection = 0;
   windSpeed = 0;
   windSpeedMPH = 0;
   lastWindIRQ = 0;
   windClicks = 0;
   lastWindCheck = 0;
}

//Alternate Constructor
WindSensor::WindSensor(int wdp, int wsp){
   windDirectionPin = wdp;
   windSpeedPin = wsp;
   windDirection = 0;
   windSpeed = 0;
   windSpeedMPH = 0;
   lastWindIRQ = 0;
   windClicks = 0;
   lastWindCheck = 0;
}
  
// Activated by the magnet in the anemometer (2 ticks per rotation), attached to input D3
void WindSensor::wspeedIRQ(){
    if (millis() - lastWindIRQ > 10) // Ignore switch-bounce glitches less than 10ms (142MPH max reading) after the reed switch closes
    {
        lastWindIRQ = millis(); //Grab the current time
        windClicks++; //There is 1.492MPH for each click per second.
    }
}

//Public Methods
void WindSensor::setPins(int wdp, int wsp) {
      windDirectionPin = wdp;
      windSpeedPin = wsp;
}

//to be called in setup
void WindSensor::initialize() {
    pinMode(windSpeedPin, INPUT_PULLUP); // input from wind meters windspeed sensor

    //figure out these variables
    //seconds = 0;
    //lastSecond = millis();

    // attach external interrupt pins to IRQ functions
    //attachInterrupt(1, wspeedIRQ, FALLING);
    // turn on interrupts
    //interrupts();
    Serial.println("Weather Shield online!");
}

//prints and returns wind direction
int WindSensor::readWindDirection() {
    unsigned int adc;
    adc = analogRead(windDirectionPin); // get the current reading from the sensor
    // The following table is ADC readings for the wind direction sensor output, sorted from low to high.
    // Each threshold is the midpoint between adjacent headings. The output is degrees for that ADC reading.
    // Note that these are not in compass degree order! See Weather Meters datasheet for more information.
    Serial.print("Wind Direction(MPH): ");
    if (adc < 380) Serial.println("113"); return (113);
    if (adc < 393) Serial.println("68"); return (68);
    if (adc < 414) Serial.println("90"); return (90);
    if (adc < 456) Serial.println("158"); return (158);
    if (adc < 508) Serial.println("135"); return (135);
    if (adc < 551) Serial.println("203"); return (203);
    if (adc < 615) Serial.println("180"); return (180);
    if (adc < 680) Serial.println("23"); return (23);
    if (adc < 746) Serial.println("45"); return (45);
    if (adc < 801) Serial.println("248"); return (248);
    if (adc < 833) Serial.println("225"); return (225);
    if (adc < 878) Serial.println("338"); return (338);
    if (adc < 913) Serial.println("0"); return (0);
    if (adc < 940) Serial.println("293"); return (293);
    if (adc < 967) Serial.println("315"); return (315);
    if (adc < 990) Serial.println("270"); return (270);
    return (-1); // error, disconnected?
}

//prints and returns wind speed
int WindSensor::readWindSpeedMPH() {
    float deltaTime = millis() - lastWindCheck;    //750ms

    deltaTime /= 1000.0; //Covert to seconds

    float windSpeed = (float)windClicks / deltaTime; //3 / 0.750s = 4

    windClicks = 0; //Reset and start watching for new wind
    lastWindCheck = millis();

    windSpeed *= 1.492; //4 * 1.492 = 5.968MPH
    windSpeedMPH = 0.0;
    windSpeedMPH = windSpeed;

    Serial.print("\nWind Speed mph: ");
    Serial.println(windSpeedMPH);
}
