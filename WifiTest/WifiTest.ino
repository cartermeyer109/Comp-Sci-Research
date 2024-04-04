#include <WiFi101.h>
 
char ssid[] = "StoutNonSecure";       //WiFI connecion SSID
WiFiClient client;
int status = WL_IDLE_STATUS;
 
void setup() {
  WiFi.setPins(8,7,4);
  randomSeed(analogRead(0));
  Serial.begin(9600);
 
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }
 
  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid);
 
    // wait 10 seconds for connection:
    delay(10000);
  }

  Serial.print("Connected to WiFi network: ");
  Serial.println(ssid);
 
}

void loop() {
  
}
