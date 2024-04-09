#include <WiFi101.h>

//A class to store Wifi pin vars, data vars,
//and functions. Multiple class instances can be created
//to use multiple Wifi sensors
class Wifi {
public:
//DATA MEMBERS
  String ssid;
  int status;
  int CSPin;
  int IRQPin;
  int RSTPin;

//*************************************************************************
//CONSTRUCTORS
  //default constructor
  Wifi() {
      ssid = "";
      status = 0;
      CSPin = 0;
      IRQPin = 0;
      RSTPin = 0;
  }

  //constructor that sets pins and SSID
  Wifi(String s, int cs, int irq, int rst)
      :ssid(s), CSPin(cs), IRQPin(irq), RSTPin(rst) {}

  //*************************************************************************
  //MEMBER FUNCTIONS
    //To be called in setup
  void initialize() {
      WiFiClient client;
      status = WL_IDLE_STATUS;
      WiFi.setPins(CSPin, IRQPin, RSTPin);
      randomSeed(analogRead(0));
      // check for the presence of the shield:
      if (WiFi.status() == WL_NO_SHIELD) {
          Serial.println("WiFi shield not present");
          // don't continue:
          while (true);
      }
      else {
          Serial.println("WiFi shield is present");
      }
  }

  //Sets all the pins
  void setPins(int cs, int irq, int rst) {
      CSPin = cs;
      IRQPin = irq;
      RSTPin = rst;
  }

  void setSSID(String s) {
      ssid = s;
  }

  //Code does not leave the function until the wifi is connected
  //So, program will not continue if wifi foes not connect
  void forceConnect() {
    while ( status != WL_CONNECTED) {
      Serial.print("Attempting to connect to: ");
      Serial.println(ssid);
      status = WiFi.begin(ssid);
   
      // wait 10 seconds for connection:
      delay(10000);
    }
  }

  //Attemps a connection one time
  void attemptConnect() {
    status = WiFi.begin(ssid);
    if (status != WL_CONNECTED) {
      Serial.print("WiFi not connected");
    }
    else {
      Serial.print("WiFi is connected");
    }
  }

  void printWiFiData() {
    // print your WiFi shield's IP address:
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);
    Serial.println(ip);
  
    // print your MAC address:
    byte mac[6];
    WiFi.macAddress(mac);
    Serial.print("MAC address: ");
    printMacAddress(mac);
  
    // print your subnet mask:
    IPAddress subnet = WiFi.subnetMask();
    Serial.print("NetMask: ");
    Serial.println(subnet);
  
    // print your gateway address:
    IPAddress gateway = WiFi.gatewayIP();
    Serial.print("Gateway: ");
    Serial.println(gateway);
  }
  
  void printCurrentNet() {
    // print the SSID of the network you're attached to:
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());
  
    // print the MAC address of the router you're attached to:
    byte bssid[6];
    WiFi.BSSID(bssid);
    Serial.print("BSSID: ");
    printMacAddress(bssid);
  
    // print the received signal strength:
    long rssi = WiFi.RSSI();
    Serial.print("signal strength (RSSI):");
    Serial.println(rssi);
  
    // print the encryption type:
    byte encryption = WiFi.encryptionType();
    Serial.print("Encryption Type:");
    Serial.println(encryption, HEX);
  }
  
  void printMacAddress(byte mac[]) {
    for (int i = 5; i >= 0; i--) {
      if (mac[i] < 16) {
        Serial.print("0");
      }
      Serial.print(mac[i], HEX);
      if (i > 0) {
        Serial.print(":");
      }
    }
    Serial.println();
  }

  bool checkConnection() {
    if (status == WL_CONNECTED) return true;
    return false;
  }

  //TODO maybe need sleep and wake??
};
