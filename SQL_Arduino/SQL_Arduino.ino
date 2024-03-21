#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <MySQL_Encrypt_Sha1.h>
#include <MySQL_Packet.h>

#include <SPI.h>
#include <WiFi101.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
const char hostname[] = "localhost"; // change to your server's hostname/URL
const char user[] = "root";               // MySQL user login username
const char password[] = "1111";         // MySQL user login password

LiquidCrystal_I2C lcd(0x27, 16, 2);
double n1;
double n2;
double n3;

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

  lcd.setCursor(0,0);
  lcd.print("n1: ");
  lcd.setCursor(8,0);
  lcd.print(n1);
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("n2: ");
  lcd.setCursor(8,1);
  lcd.print(n2);
  delay(1000);
  lcd.setCursor(0,0);
  lcd.print("n3: ");
  lcd.setCursor(8,0);
  lcd.print(n3);
  delay(1000);
}
