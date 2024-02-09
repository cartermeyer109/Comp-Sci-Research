/*
  SD card read/write

  This example shows how to read and write data to and from an SD card file
  The circuit:
   SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

  created   Nov 2010
  by David A. Mellis
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

*/

//Declare Libraries
#include <SPI.h>
#include <SD.h>

//Declare file to readwrite to
File myFile;

//Declare CS Pin
//**Change as Needed
const int chipSelect = 53;

//
int version = 0;


void setup() {
  // Open serial communications and wait for port to open:
  // It is always 9600
  Serial.begin(9600);
  
  //Waiting to continue the program until serial is connected
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  //Different from serial.begin()
  //Sets to the correct pin automatically,
  //but can manually set to the SS pin which is 53
  if (!SD.begin()) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  String temp;

  //Reads the number from the prior file
  myFile = SD.open("test.txt");
  if (myFile.available()) {
    temp = myFile.read();

    //I suppose 0 in integer translates to 48 in ASCII value
    version = temp.toInt() - 47;
    
    Serial.println(version);
    
  }
  

  myFile.close();

  //Resets the file
  SD.remove("test.txt");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("test.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");

    //This writes to the file
    myFile.println(version);
    
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

  // re-open the file for reading:
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

void loop() {
  // nothing happens after setup
}
