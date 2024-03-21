#include <WiFi101.h>

char ssid[] = "StoutNonSecured";     //  your network SSID (name) 
char pass[] = "";    // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

void setup() {
  // initialize serial:
  Serial.begin(9600);
  Serial.println("Attempting to connect to WPA2 network...");
  status = WiFi.begin(ssid);

  // if you're not connected, stop here:
 
    while(status != WL_CONNECTED){
      delay(10000);
      Serial.begin(9600);
      Serial.println("Attempting to connect to WPA2 network...");
      status = WiFi.begin(ssid);
    }
  // if you are connected, print out info about the connection:
    Serial.println("Connected to network");
  
}

void loop() {
  // do nothing
}
