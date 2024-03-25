

#include <SPI.h>
#include <WiFi101.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
const char hostname[] = "localhost"; // change to your server's hostname/URL
const char user[] = "root";               // MySQL user login username
const char password[] = "1111";         // MySQL user login password

LiquidCrystal_I2C lcd(0x27, 8, 2);
double n1;
double n2;
double n3;
double n4 = 0;

void setup() {
  WiFi.setPins(8,7,4);
  Serial.begin(9600);
  randomSeed(analogRead(0));
  lcd.init();
  lcd.backlight();
}

void loop() {
  delay(1000);
  Serial.println("Generating Random Numbers");
  n1 = random(0, 100);
  n2 = random(0, 100);
  n3 = random(0, 100);

  
  
  lcd.print(n4);
  n4++;
}
