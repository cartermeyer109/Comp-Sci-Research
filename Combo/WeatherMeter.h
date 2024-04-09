#include "SparkFun_Weather_Meter_Kit_Arduino_Library.h"

//A class to store weather meter's pin vars and functions.
// Multiple instance can be created to use multiple weather meters
class WeatherMeter {
public:
//DATA MEMBERS
    int windDirectionPin;
    int windSpeedPin;
    int rainfallPin;
    SFEWeatherMeterKit kit = SFEWeatherMeterKit(0, 0, 0);
    float windDirection;
    float windSpeed;
    //float rainfall;


//*************************************************************************
//CONSTRUCTORS
    //default constructor
    WeatherMeter() {
        windDirectionPin = 0;
        windSpeedPin = 0;
        rainfallPin = 0;
        windDirection = 0;
        windSpeed = 0;
        //rainfall = 0;
    }

    //consturctor to set all pins
    WeatherMeter(int wdp, int wsp, int rp) :
        windDirectionPin(wdp), windSpeedPin(wsp), rainfallPin(rp){
            kit = SFEWeatherMeterKit(windDirectionPin, windSpeedPin, rainfallPin);
            windDirection = 0;
            windSpeed = 0;
            //rainfall = 0;
    }

    //consturctor to set windDirection and rainfall pins,
    //but not the windspeed pin
    WeatherMeter(int wdp, int rp) :
        windDirectionPin(wdp), rainfallPin(rp){
            kit = SFEWeatherMeterKit(windDirectionPin, windDirectionPin, rainfallPin);
            windSpeedPin = 0;
            windDirection = 0;
            windSpeed = 0;
            //rainfall = 0;
    }

//*************************************************************************
//MEMBER FUNCTIONS
    //To be called in setup
    //TODO the example of this sensor uses a unique serial 115200
    void initialize() {
        #ifdef SFE_WMK_PLAFTORM_UNKNOWN
            // The platform you're using hasn't been added to the library, so the
            // expected ADC values have been calculated assuming a 10k pullup resistor
            // and a perfectly linear 16-bit ADC. Your ADC likely has a different
            // resolution, so you'll need to specify it here:
            kit.setADCResolutionBits(10);

            Serial.println(F("Unknown platform! Please edit the code with your ADC resolution!"));
            Serial.println();
        #endif

            // Begin weather meter kit
            kit.begin();
    }
    
    //prints and returns wind direction
    int readWindDirection() {
        Serial.println(F("Wind direction (degrees): "));
        windDirection = kit.getWindDirection();
        Serial.println(windDirection, 1);
        return windDirection;
    }

    //prints and returns wind speed
    int readWindSpeed() {
        Serial.println(F("Wind speed (kph): "));
        windSpeed = kit.getWindSpeed();
        Serial.println(windSpeed, 1);
        return windSpeed;
    }

//    //prints and return total rainfall
//    int readRainfall() {
//        Serial.println(F("Rainfall (mm): "));
//        rainfall = kit.getTotalRainfall();
//        Serial.println(rainfall, 1);
//        return rainfall;
//    }
};

// Pins for Weather Carrier with ESP32 Processor Board
//int windDirectionPin = 35;
//int windSpeedPin = 14;
//int rainfallPin = 27;

// Pins for the Weather Shield with SparkFun RedBoard Qwiic or Arduino Uno
// int windDirectionPin = A0;
// int windSpeedPin = 3;
// int rainfallPin = 2;
