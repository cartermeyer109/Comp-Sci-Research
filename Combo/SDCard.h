#include <SPI.h>
#include <SD.h>

//A class to store SD card vars and
//functions. Multiple class instances can be created
//to use SD cards/readers
class SDCard {
public:
//DATA MEMBERS
  Sd2Card card;
  SdVolume volume;
  SdFile root;
  int chipSelectPin;
  File myFile;
  
//*************************************************************************
//CONSTRUCTORS
  //default constructor
  SDCard() {
    chipSelectPin = 0;
  }
  
  //constructor that sets sunPin and resetPin
  SDCard(int csp):chipSelectPin(csp){}
  
//*************************************************************************
//MEMBER FUNCTIONS
  //To be called in setup
  void initialize() {
    Serial.print("\nInitializing SD card...");
  
    // we'll use the initialization code from the utility libraries
    // since we're just testing if the card is working!
    if (!card.init(SPI_HALF_SPEED, chipSelectPin)) {
      Serial.println("initialization failed. Things to check:");
      Serial.println("* is a card inserted?");
      Serial.println("* is your wiring correct?");
      Serial.println("* did you change the chipSelectPin to match your shield or module?");
      while (1);
    } else {
      Serial.println("Wiring is correct and a card is present.");
    }
  
    // print the type of card
    Serial.println();
    Serial.print("Card type:         ");
    switch (card.type()) {
      case SD_CARD_TYPE_SD1:
        Serial.println("SD1");
        break;
      case SD_CARD_TYPE_SD2:
        Serial.println("SD2");
        break;
      case SD_CARD_TYPE_SDHC:
        Serial.println("SDHC");
        break;
      default:
        Serial.println("Unknown");
    }
  
    // Now we will try to open the 'volume'/'partition' - it should be FAT16 or FAT32
    if (!volume.init(card)) {
      Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
      while (1);
    }
  
    Serial.print("Clusters:          ");
    Serial.println(volume.clusterCount());
    Serial.print("Blocks x Cluster:  ");
    Serial.println(volume.blocksPerCluster());
  
    Serial.print("Total Blocks:      ");
    Serial.println(volume.blocksPerCluster() * volume.clusterCount());
    Serial.println();
  
    // print the type and size of the first FAT-type volume
    uint32_t volumesize;
    Serial.print("Volume type is:    FAT");
    Serial.println(volume.fatType(), DEC);
  
    volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
    volumesize *= volume.clusterCount();       // we'll have a lot of clusters
    volumesize /= 2;                           // SD card blocks are always 512 bytes (2 blocks are 1KB)
    Serial.print("Volume size (Kb):  ");
    Serial.println(volumesize);
    Serial.print("Volume size (Mb):  ");
    volumesize /= 1024;
    Serial.println(volumesize);
    Serial.print("Volume size (Gb):  ");
    Serial.println((float)volumesize / 1024.0);
  
    Serial.println("\nFiles found on the card (name, date and size in bytes): ");
    root.openRoot(volume);
  
    // list all files in the card with date and size
    root.ls(LS_R | LS_DATE | LS_SIZE);
  }

  //Write a message to a file
  void writeToFile(String file, String message) {
    // open the file. note that only one file can be open at a time,
    // so you have to close this one before opening another.
    myFile = SD.open(file, FILE_WRITE);
  
    // if the file opened okay, write to it:
    if (myFile) {
      Serial.print("Writing to file...");
      myFile.println(message);
      // close the file:
      myFile.close();
      Serial.println("done.");
    } else {
      // if the file didn't open, print an error:
      Serial.println("error opening file");
    }
  }

  //Reads an entire file
  void readFile(String file) {
    myFile = SD.open(file);
    if (myFile) {
      //Serial.println("test.txt:");
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
};

//****************************************
//The actual pin select for mega board is
//VCC: 5V
//GND: GND
//MISO:50
//MOSI:51
//SCK:52
//CS/SS:53
//****************************************
